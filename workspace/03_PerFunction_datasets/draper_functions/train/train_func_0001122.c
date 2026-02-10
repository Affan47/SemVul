get_app_version_anonymous(
    APP& app, bool need_64b, bool reliable_only
) {
    unsigned int i;
    CLIENT_APP_VERSION* best = NULL;
    bool found = false;
    char message[256];

    if (config.debug_version_select) {
        log_messages.printf(MSG_NORMAL,
            "[version] get_app_version_anonymous: app %s%s\n",
            app.name, reliable_only?" (reliable only)":""
        );
    }
    for (i=0; i<g_request->client_app_versions.size(); i++) {
        CLIENT_APP_VERSION& cav = g_request->client_app_versions[i];
        if (!cav.app) continue;
        if (cav.app->id != app.id) {
            continue;
        }
        if (need_64b && !is_64b_platform(cav.platform)) {
            continue;
        }
        int gavid = host_usage_to_gavid(cav.host_usage, app);
        if (reliable_only && !app_version_is_reliable(gavid)) {
            if (config.debug_version_select) {
                log_messages.printf(MSG_NORMAL,
                    "[version] %d %s not reliable\n",
                    cav.version_num, cav.plan_class
                );
            }
            continue;
        }
        if (daily_quota_exceeded(gavid, cav.host_usage)) {
            if (config.debug_version_select) {
                log_messages.printf(MSG_NORMAL,
                    "[version] %d %s daily quota exceeded\n",
                    cav.version_num, cav.plan_class
                );
            }
            continue;
        }
        if (cav.version_num < app.min_version) {
            if (config.debug_version_select) {
                log_messages.printf(MSG_NORMAL,
                    "[version] %d %s version < min version\n",
                    cav.version_num, cav.plan_class
                );
            }
            continue;
        }
        found = true;
        if (!need_this_resource(cav.host_usage, NULL, &cav)) {
            if (config.debug_version_select) {
                log_messages.printf(MSG_NORMAL,
                    "[version] %d %s don't need resource\n",
                    cav.version_num, cav.plan_class
                );
            }
            continue;
        }
        if (best) {
            if (cav.host_usage.projected_flops > best->host_usage.projected_flops) {
                best = &cav;
            }
        } else {
            best = &cav;
        }
    }
    if (!best) {
        if (config.debug_version_select) {
            log_messages.printf(MSG_NORMAL,
                "[version] Didn't find anonymous platform app for %s\n",
                app.name
            );
        }
    }
    if (!found) {
        sprintf(message,
            "%s %s.",
            _("Your app_info.xml file doesn't have a usable version of"),
            app.user_friendly_name
        );
        add_no_work_message(message);
    }
    return best;
}

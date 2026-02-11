lookup_app_version(
    APP* app, char* platform, int version_num, char* plan_class
) {
    for (unsigned int i=0; i<app_versions.size(); i++) {
        APP_VERSION* avp = app_versions[i];
        if (avp->app != app) continue;
        if (version_num != avp->version_num) continue;
        if (strcmp(avp->platform, platform)) continue;
        if (strcmp(avp->plan_class, plan_class)) continue;
        return avp;
    }
    return 0;
}

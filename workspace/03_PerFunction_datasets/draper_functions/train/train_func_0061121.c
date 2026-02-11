add_project(
    const char* master_url, const char* _auth, const char* project_name,
    bool attached_via_acct_mgr
) {
    char path[MAXPATHLEN], canonical_master_url[256], auth[256];
    PROJECT* project;
    FILE* f;
    int retval;

    if (config.disallow_attach) {
        return ERR_USER_PERMISSION;
    }

    safe_strcpy(canonical_master_url, master_url);
    strip_whitespace(canonical_master_url);
    canonicalize_master_url(canonical_master_url, sizeof(canonical_master_url));
    if (!valid_master_url(canonical_master_url)) {
        msg_printf(0, MSG_INFO, "Invalid URL: %s", canonical_master_url);
        return ERR_INVALID_URL;
    }

    safe_strcpy(auth, _auth);
    strip_whitespace(auth);
    if (!strlen(auth)) {
        msg_printf(0, MSG_INFO, "Missing account key");
        return ERR_AUTHENTICATOR;
    }


    if (lookup_project(canonical_master_url)) {
        msg_printf(0, MSG_INFO, "Already attached to %s", canonical_master_url);
        return ERR_ALREADY_ATTACHED;
    }


    project = new PROJECT;
    safe_strcpy(project->master_url, canonical_master_url);
    safe_strcpy(project->authenticator, auth);
    safe_strcpy(project->project_name, project_name);
    project->attached_via_acct_mgr = attached_via_acct_mgr;

    retval = project->write_account_file();
    if (retval) return retval;

    get_account_filename(canonical_master_url, path);
    f = boinc_fopen(path, "r");
    if (!f) return ERR_FOPEN;
    retval = project->parse_account(f);
    fclose(f);
    if (retval) return retval;


    sprintf(path, "%s/%s", project->project_dir(), APP_INFO_FILE_NAME);
    if (boinc_file_exists(path)) {
        project->anonymous_platform = true;
        f = fopen(path, "r");
        if (f) {
            parse_app_info(project, f);
            fclose(f);
        }
    } else {
        retval = remove_project_dir(*project);
    }

    retval = make_project_dir(*project);
    if (retval) return retval;
    projects.push_back(project);
    project->sched_rpc_pending = RPC_REASON_INIT;
    set_client_state_dirty("Add project");
    return 0;
}

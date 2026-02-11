am_restore_lasso_profile_state(request_rec *r,
                                           LassoProfile *profile,
                                           am_cache_entry_t *am_session)
{
    const char *identity_dump;
    const char *session_dump;
    int rc;


    if(am_session == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Could not get auth_mellon session while attempting"
                      " to restore the lasso profile state.");
        return;
    }

    identity_dump = am_cache_get_lasso_identity(am_session);
    if(identity_dump != NULL) {
        rc = lasso_profile_set_identity_from_dump(profile, identity_dump);
        if(rc < 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Could not restore identity from dump."
                          " Lasso error: [%i] %s", rc, lasso_strerror(rc));
            am_release_request_session(r, am_session);
        }
    }

    session_dump = am_cache_get_lasso_session(am_session);
    if(session_dump != NULL) {
        rc = lasso_profile_set_session_from_dump(profile, session_dump);
        if(rc < 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Could not restore session from dump."
                          " Lasso error: [%i] %s", rc, lasso_strerror(rc));
            am_release_request_session(r, am_session);
        }
    }
}

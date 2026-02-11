mwa_cache_keyring(server_rec *serv, struct server_config *sconf)
{
    int status;
    enum webauth_kau_status kau_status;
    int update_status;

    status = webauth_keyring_auto_update(sconf->ctx, sconf->keyring_path,
                 sconf->keyring_auto_update,
                 sconf->keyring_auto_update ? sconf->keyring_key_lifetime : 0,
                 &sconf->ring, &kau_status, &update_status);
    if (status != WA_ERR_NONE)
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, serv,
                     "mod_webauth: opening keyring %s failed: %s",
                     sconf->keyring_path,
                     webauth_error_message(sconf->ctx, status));
    if (kau_status == WA_KAU_UPDATE && update_status != WA_ERR_NONE)
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, serv,
                     "mod_webauth: updating keyring %s failed: %s",
                     sconf->keyring_path,
                     webauth_error_message(sconf->ctx, update_status));

    if (sconf->debug) {
        const char *msg;

        if (kau_status == WA_KAU_NONE)
            msg = "opened";
        else if (kau_status == WA_KAU_CREATE)
            msg = "create";
        else if (kau_status == WA_KAU_UPDATE)
            msg = "updated";
        else
            msg = "<unknown>";
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, serv,
                     "mod_webauth: %s key ring: %s", msg, sconf->keyring_path);
    }

    return status;
}

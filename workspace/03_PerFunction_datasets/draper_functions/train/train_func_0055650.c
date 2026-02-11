change_sie_password(const char *name, char *query, void* arg, request_rec *r)
{
    FILE       *f;
    char       *uid=NULL , *col=NULL, *origpw_hash=NULL;
    char       *newpw = NULL;
    char       filename[BIG_LINE];
    char       inbuf[BIG_LINE];
    char       outbuf[64];
    char       *bindpw = (char *)apr_table_get(r->notes, RQ_NOTES_USERPW);
    int        admpwd_done = 0;

    apr_snprintf(filename, sizeof(filename), "%s/admpw", configdir);

    if (query==NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                      "Wrong usage, password param missing");
        return 0;
    }

    if ((f=fopen(filename, "r"))==NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                      "Can not open admpw file [%s]", filename);
        return 0;
    }
    if (fgets(inbuf, sizeof(inbuf), f) == NULL) {
        fclose(f);
        ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                      "Can not read admpw file [%s]", filename);
        return 0;
    }
    fclose(f);

    col = strchr(inbuf, ':');
    if (col == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_CRIT, 0, r,
                      "admpw file [%s] is corrupted", filename);
        return 0;
    }

    uid = inbuf; *col=0; origpw_hash=col+1;


    newpw = strdup(query);
    if (NULL == newpw) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
           "failed to allocate memory for password");
        goto recover;
    }
    ap_unescape_url(newpw);
    apr_sha1_base64(newpw, strlen(newpw), outbuf);
    if (!update_admpwd(configdir, uid, outbuf)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
           "failed to update admpw");
        goto recover;
    }
    admpwd_done = 1;

    if (!task_update_registry_server_bindpw(uid, newpw, bindpw, r)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, NULL,
            "failed to update server bindpw");
        goto recover;
    }

    return 1;

recover:
    if (newpw) {
        free(newpw);
    }
    if (admpwd_done) {
        update_admpwd(configdir, uid, origpw_hash);
    }
    return 0;
}

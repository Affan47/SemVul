nss_hook_Auth(request_rec *r)
{
    SSLDirConfigRec *dc = myDirConfig(r);

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, r->server, "nss_hook_Auth");


    if ((dc->nOptions & SSL_OPT_STRICTREQUIRE) &&
        (apr_table_get(r->notes, "ssl-access-forbidden")))
    {
        return HTTP_FORBIDDEN;
    }

    return DECLINED;
}

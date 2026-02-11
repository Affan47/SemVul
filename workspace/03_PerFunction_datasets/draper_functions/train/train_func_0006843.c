handler_redirect(request_rec *r)
{
    if (strcmp(r->handler, "redirect-handler")) {
        return DECLINED;
    }


    if (strncmp(r->filename, "redirect:", 9) != 0) {
        return DECLINED;
    }


    ap_internal_redirect(apr_pstrcat(r->pool, r->filename+9,
                                     r->args ? "?" : NULL, r->args, NULL), r);


    return OK;
}

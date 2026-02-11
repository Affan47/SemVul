select_interp_name(request_rec *req, conn_rec *con,
                                      py_config *conf, hl_entry *hle,
                                      py_handler *fh)
{
    const char *s = NULL;

    if ((s = apr_table_get(conf->directives, "PythonInterpreter"))) {

        return s;
    }
    else {
        if ((s = apr_table_get(conf->directives, "PythonInterpPerDirectory")) && (strcmp(s, "1") == 0)) {


            if (req && ap_is_directory(req->pool, req->filename)) {


                if (req->filename[strlen(req->filename)-1]=='/') {
                    return ap_make_dirstr_parent(req->pool, req->filename);
                }
                else {
                    return ap_make_dirstr_parent(req->pool,
                                                apr_pstrcat(req->pool, req->filename,
                                                            "/", NULL ));
                }
            }
            else {
                if (req && req->filename)
                    return ap_make_dirstr_parent(req->pool, req->filename);
                else


                    return NULL;
            }
        }
        else if ((s = apr_table_get(conf->directives, "PythonInterpPerDirective")) && (strcmp(s, "1") == 0)) {


            if (fh) {
                s = fh->directory;
            }
            else if (hle) {
                s = hle->directory;
            }
            else {
                return NULL;
            }

            if (s && (s[0] == '\0'))
                return NULL;
            else
                return s;
        }
        else {

            if (con)
                return con->base_server->server_hostname;
            else
                return req->server->server_hostname;
        }
    }
}

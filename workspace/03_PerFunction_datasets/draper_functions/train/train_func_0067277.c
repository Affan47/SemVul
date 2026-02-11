ap_add_cgi_vars(request_rec *r)
{
    apr_table_t *e = r->subprocess_env;

    apr_table_setn(e, "GATEWAY_INTERFACE", "CGI/1.1");
    apr_table_setn(e, "SERVER_PROTOCOL", r->protocol);
    apr_table_setn(e, "REQUEST_METHOD", r->method);
    apr_table_setn(e, "QUERY_STRING", r->args ? r->args : "");
    apr_table_setn(e, "REQUEST_URI", original_uri(r));


    if (!strcmp(r->protocol, "INCLUDED")) {
        apr_table_setn(e, "SCRIPT_NAME", r->uri);
        if (r->path_info && *r->path_info) {
            apr_table_setn(e, "PATH_INFO", r->path_info);
        }
    }
    else if (!r->path_info || !*r->path_info) {
        apr_table_setn(e, "SCRIPT_NAME", r->uri);
    }
    else {
        int path_info_start = ap_find_path_info(r->uri, r->path_info);

        apr_table_setn(e, "SCRIPT_NAME",
                      apr_pstrndup(r->pool, r->uri, path_info_start));

        apr_table_setn(e, "PATH_INFO", r->path_info);
    }

    if (r->path_info && r->path_info[0]) {


        request_rec *pa_req;

        pa_req = ap_sub_req_lookup_uri(ap_escape_uri(r->pool, r->path_info), r,
                                       NULL);

        if (pa_req->filename) {
            char *pt = apr_pstrcat(r->pool, pa_req->filename, pa_req->path_info,
                                  NULL);
#ifdef WIN32

            apr_filepath_merge(&pt, "", pt, APR_FILEPATH_NATIVE, r->pool);
#endif
            apr_table_setn(e, "PATH_TRANSLATED", pt);
        }
        ap_destroy_sub_req(pa_req);
    }
}

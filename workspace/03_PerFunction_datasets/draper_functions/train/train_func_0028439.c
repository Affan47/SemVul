authorize_user_core(request_rec *r, int after_authn)
{
    authz_core_dir_conf *conf;
    authz_status auth_result;

    conf = ap_get_module_config(r->per_dir_config, &authz_core_module);

    if (!conf->section) {
        if (ap_auth_type(r)) {


            ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r, APLOGNO(01627)
                          "AuthType configured with no corresponding "
                          "authorization directives");

            return HTTP_INTERNAL_SERVER_ERROR;
        }

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(01628)
                      "authorization result: granted (no directives)");

        return OK;
    }

    auth_result = apply_authz_sections(r, conf->section, AUTHZ_LOGIC_AND);

    if (auth_result == AUTHZ_GRANTED) {
        return OK;
    }
    else if (auth_result == AUTHZ_DENIED_NO_USER) {
        if (after_authn) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r, APLOGNO(01629)
                          "authorization failure (no authenticated user): %s",
                          r->uri);


            if (r->user)
                ap_note_auth_failure(r);

            return HTTP_UNAUTHORIZED;
        }
        else {


            return DECLINED;
        }
    }
    else if (auth_result == AUTHZ_DENIED || auth_result == AUTHZ_NEUTRAL) {
        if (!after_authn || ap_auth_type(r) == NULL) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r, APLOGNO(01630)
                          "client denied by server configuration: %s%s",
                          r->filename ? "" : "uri ",
                          r->filename ? r->filename : r->uri);

            return HTTP_FORBIDDEN;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, APR_SUCCESS, r, APLOGNO(01631)
                          "user %s: authorization failure for \"%s\": ",
                          r->user, r->uri);

            if (conf->authz_forbidden_on_fail > 0) {
                return HTTP_FORBIDDEN;
            }
            else {


                if (r->user)
                    ap_note_auth_failure(r);
                return HTTP_UNAUTHORIZED;
            }
        }
    }
    else {


        return HTTP_INTERNAL_SERVER_ERROR;
    }
}

am_auth_mellon_user(request_rec *r)
{
    am_dir_cfg_rec *dir = am_get_dir_cfg(r);
    int return_code = HTTP_UNAUTHORIZED;
    am_cache_entry_t *session;


    if (r->main)
        return OK;


    if(dir->enable_mellon == am_enable_off
       || dir->enable_mellon == am_enable_default) {
	return DECLINED;
    }


    am_set_nocache(r);


    if(strstr(r->uri, dir->endpoint_path) == r->uri) {

        return OK;
    }


    session = am_get_request_session(r);


    if(dir->enable_mellon == am_enable_auth) {


        if(session == NULL || !session->logged_in) {


            if(session) {

                am_release_request_session(r, session);
            }


            return am_start_auth(r);
        }


        return_code = am_check_permissions(r, session);
        if(return_code != OK) {
            am_release_request_session(r, session);

            return return_code;
        }


        am_cache_env_populate(r, session);


        am_release_request_session(r, session);

        return OK;

    } else {


        if(session != NULL
           && session->logged_in
           && am_check_permissions(r, session) == OK) {


            am_cache_env_populate(r, session);
        }

        if(session != NULL) {

            am_release_request_session(r, session);
        }


        return DECLINED;
    }
}

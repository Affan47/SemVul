json_rpc2_call_recur(CURL *curl, const char *url,
              const char *userpass, json_t *rpc_req,
              int *curl_err, int flags, int recur) {
    if(recur >= 5) {
        if(opt_debug)
            applog(LOG_DEBUG, "Failed to call rpc command after %i tries", recur);
        return NULL;
    }
    if(!strcmp(rpc2_id, "")) {
        if(opt_debug)
            applog(LOG_DEBUG, "Tried to call rpc2 command before authentication");
        return NULL;
    }
    json_t *params = json_object_get(rpc_req, "params");
    if (params) {
        json_t *auth_id = json_object_get(params, "id");
        if (auth_id) {
            json_string_set(auth_id, rpc2_id);
        }
    }
    json_t *res = json_rpc_call(curl, url, userpass, json_dumps(rpc_req, 0),
            curl_err, flags | JSON_RPC_IGNOREERR);
    if(!res) goto end;
    json_t *error = json_object_get(res, "error");
    if(!error) goto end;
    json_t *message;
    if(json_is_string(error))
        message = error;
    else
        message = json_object_get(error, "message");
    if(!message || !json_is_string(message)) goto end;
    const char *mes = json_string_value(message);
    if(!strcmp(mes, "Unauthenticated")) {
        pthread_mutex_lock(&rpc2_login_lock);
        rpc2_login(curl);
        sleep(1);
        pthread_mutex_unlock(&rpc2_login_lock);
        return json_rpc2_call_recur(curl, url, userpass, rpc_req,
            curl_err, flags, recur + 1);
    } else if(!strcmp(mes, "Low difficulty share") || !strcmp(mes, "Block expired") || !strcmp(mes, "Invalid job id") || !strcmp(mes, "Duplicate share")) {
        json_t *result = json_object_get(res, "result");
        if(!result) {
            goto end;
        }
        json_object_set(result, "reject-reason", json_string(mes));
    } else {
        applog(LOG_ERR, "json_rpc2.0 error: %s", mes);
        return NULL;
    }
    end:
    return res;
}

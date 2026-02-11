stratum_handle_method(struct stratum_ctx *sctx, const char *s)
{
	json_t *val, *id, *params;
	json_error_t err;
	const char *method;
	bool ret = false;

	val = JSON_LOADS(s, &err);
	if (!val) {
		applog(LOG_ERR, "JSON decode failed(%d): %s", err.line, err.text);
		goto out;
	}

	method = json_string_value(json_object_get(val, "method"));
	if (!method)
		goto out;
	id = json_object_get(val, "id");
	params = json_object_get(val, "params");

    if (jsonrpc_2) {
        if (!strcasecmp(method, "job")) {
            ret = stratum_2_job(sctx, params);
            goto out;
        }
    } else {
        if (!strcasecmp(method, "mining.notify")) {
            ret = stratum_notify(sctx, params);
            goto out;
        }
        if (!strcasecmp(method, "mining.set_difficulty")) {
            ret = stratum_set_difficulty(sctx, params);
            goto out;
        }
        if (!strcasecmp(method, "client.reconnect")) {
            ret = stratum_reconnect(sctx, params);
            goto out;
        }
        if (!strcasecmp(method, "client.get_version")) {
            ret = stratum_get_version(sctx, id);
            goto out;
        }
        if (!strcasecmp(method, "client.show_message")) {
            ret = stratum_show_message(sctx, id, params);
            goto out;
        }
    }

out:
	if (val)
		json_decref(val);

	return ret;
}

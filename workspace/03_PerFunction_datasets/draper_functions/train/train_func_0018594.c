cfg_parse_boolean(cfg_parser_t *pctx, const cfg_type_t *type, cfg_obj_t **ret)
{
	isc_result_t result;
	isc_boolean_t value;
	cfg_obj_t *obj = NULL;
	UNUSED(type);

	result = cfg_gettoken(pctx, 0);
	if (result != ISC_R_SUCCESS)
		return (result);

	if (pctx->token.type != isc_tokentype_string)
		goto bad_boolean;

	if ((strcasecmp(TOKEN_STRING(pctx), "true") == 0) ||
	    (strcasecmp(TOKEN_STRING(pctx), "yes") == 0) ||
	    (strcmp(TOKEN_STRING(pctx), "1") == 0)) {
		value = ISC_TRUE;
	} else if ((strcasecmp(TOKEN_STRING(pctx), "false") == 0) ||
		   (strcasecmp(TOKEN_STRING(pctx), "no") == 0) ||
		   (strcmp(TOKEN_STRING(pctx), "0") == 0)) {
		value = ISC_FALSE;
	} else {
		goto bad_boolean;
	}

	CHECK(cfg_create_obj(pctx, &cfg_type_boolean, &obj));
	obj->value.boolean = value;
	*ret = obj;
	return (result);

 bad_boolean:
	cfg_parser_error(pctx, CFG_LOG_NEAR, "boolean expected");
	return (ISC_R_UNEXPECTEDTOKEN);

 cleanup:
	return (result);
}

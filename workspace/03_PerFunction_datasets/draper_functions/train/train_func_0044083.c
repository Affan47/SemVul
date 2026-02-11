parse_portrange(cfg_parser_t *pctx, const cfg_type_t *type, cfg_obj_t **ret) {
	isc_result_t result;
	cfg_obj_t *obj = NULL;

	UNUSED(type);

	CHECK(cfg_peektoken(pctx, ISC_LEXOPT_NUMBER | ISC_LEXOPT_CNUMBER));
	if (pctx->token.type == isc_tokentype_number)
		CHECK(parse_port(pctx, ret));
	else {
		CHECK(cfg_gettoken(pctx, 0));
		if (pctx->token.type != isc_tokentype_string ||
		    strcasecmp(TOKEN_STRING(pctx), "range") != 0) {
			cfg_parser_error(pctx, CFG_LOG_NEAR,
					 "expected integer or 'range'");
			return (ISC_R_UNEXPECTEDTOKEN);
		}
		CHECK(cfg_create_tuple(pctx, &cfg_type_porttuple, &obj));
		CHECK(parse_port(pctx, &obj->value.tuple[0]));
		CHECK(parse_port(pctx, &obj->value.tuple[1]));
		if (obj->value.tuple[0]->value.uint32 >
		    obj->value.tuple[1]->value.uint32) {
			cfg_parser_error(pctx, CFG_LOG_NOPREP,
					 "low port '%u' must not be larger "
					 "than high port",
					 obj->value.tuple[0]->value.uint32);
			result = ISC_R_RANGE;
			goto cleanup;
		}
		*ret = obj;
		obj = NULL;
	}

 cleanup:
	if (obj != NULL)
		cfg_obj_destroy(pctx, &obj);
	return (result);
}

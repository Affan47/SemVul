validate_saml11_message(Icx_ctx *ctx, xmlDocPtr token_doc)
{
  int result;
  xmlSchemaPtr schema;
  xmlSchemaParserCtxtPtr schema_ctx;
  xmlSchemaValidCtxtPtr validator;
  xmlNodePtr root;
  xmlChar *MajorVersion;
  xmlChar *MinorVersion;

  schema_ctx =
	xmlSchemaNewMemParserCtxt((const char *) oasis_sstc_saml_schema_assertion_1_1,
							  sizeof(oasis_sstc_saml_schema_assertion_1_1));
  if (schema_ctx == NULL) {
	log_msg((LOG_ERROR_LEVEL, "Unable to create schema parsing context"));
	return(-1);
  }

  schema = xmlSchemaParse(schema_ctx);
  if (schema == NULL) {
	log_msg((LOG_ERROR_LEVEL, "Unable to parse schema"));
	xmlSchemaFreeParserCtxt(schema_ctx);
	return(-1);
  }

  validator = xmlSchemaNewValidCtxt(schema);
  if (validator == NULL) {
	log_msg((LOG_ERROR_LEVEL, "Unable to create schema validator context"));
	xmlSchemaFree(schema);
	xmlSchemaFreeParserCtxt(schema_ctx);
	return(-1);
  }

  xmlSchemaSetValidErrors(validator, saml11_validity_err_rep,
						  saml11_validity_warn_rep, ctx);

  result = xmlSchemaValidateDoc(validator, token_doc);
  xmlSchemaFreeValidCtxt(validator);
  xmlSchemaFree(schema);
  xmlSchemaFreeParserCtxt(schema_ctx);

  if (result != 0) {
	log_msg((LOG_ERROR_LEVEL, "Schema validation of SAML 1.1 token failed"));
	return(-1);
  }


  root = xmlDocGetRootElement(token_doc);
  MajorVersion = xmlGetNoNsProp(root, ATTR_MAJOR_VERSION);
  if (!xmlStreq(MajorVersion, (xmlChar *) "1")) {
	log_msg((LOG_ERROR_LEVEL, "Unexpected SAML major version received"));
	xmlFree(MajorVersion);
	return(-1);
  }
  xmlFree(MajorVersion);

  MinorVersion = xmlGetNoNsProp(root, ATTR_MINOR_VERSION);
  if (!xmlStreq(MinorVersion, (xmlChar *) "1")
	  && !xmlStreq(MinorVersion, (xmlChar *) "0")) {
	log_msg((LOG_ERROR_LEVEL, "Unexpected SAML minor version received"));
	xmlFree(MinorVersion);
	return(-1);
  }

  xmlFree(MinorVersion);

  return(1);
}

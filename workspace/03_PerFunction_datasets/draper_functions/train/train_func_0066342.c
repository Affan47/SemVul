icx_load_key(Icx_ctx *ctx, const char *key_file_name, const char *password)
{
  xmlSecKeyPtr key;

  if (key_file_name == NULL || *key_file_name == '\0') {
	log_msg((LOG_ERROR_LEVEL, "Certificate file name is missing"));
	return(-1);
  }

  key = xmlSecCryptoAppKeyLoad(key_file_name, xmlSecKeyDataFormatPem,
							   password, NULL, NULL);
  if (key == NULL) {
	log_msg((LOG_ERROR_LEVEL, "Unable to find or use certificate file"));
	return(-1);
  }


  if (xmlSecKeySetName(key, BAD_CAST key_file_name) < 0) {
	log_msg((LOG_ERROR_LEVEL, "Failed to set key name"));
	xmlSecKeyDestroy(key);
	return(-1);
  }


  if (xmlSecCryptoAppDefaultKeysMngrAdoptKey(ctx->key_manager, key) < 0) {
	log_msg((LOG_ERROR_LEVEL, "Failed to add key to keys manager"));
	xmlSecKeyDestroy(key);
	return(-1);
  }

  return(1);
}

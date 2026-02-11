__config_new(cmph_io_adapter_t *key_source)
{
	cmph_config_t *mph = (cmph_config_t *)malloc(sizeof(cmph_config_t));
	memset(mph, 0, sizeof(cmph_config_t));
	if (mph == NULL) return NULL;
	mph->key_source = key_source;
	mph->verbosity = 0;
	mph->data = NULL;
	mph->c = 0;
	return mph;
}

get_version_capa(struct client *client,
		 int32_t *version, int32_t *capa,
		 char **version_str)
{
    put32(client, eGetVersionAndCapabilities);
    ret32(client, *version);
    ret32(client, *capa);
    retstring(client, *version_str);
    return GSMERR_OK;
}

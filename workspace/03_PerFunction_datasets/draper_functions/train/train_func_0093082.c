BuildName(const char* client_name, char* res, const char* dir, int which, int size)
{
    char ext_client_name[SYNC_MAX_NAME_SIZE + 1];
    JackTools::RewriteName(client_name, ext_client_name);
    if (getenv("JACK_PROMISCUOUS_SERVER")) {
	    snprintf(res, size, "%s/jack_%s_%d", dir, ext_client_name, which);
    } else {
	    snprintf(res, size, "%s/jack_%s_%d_%d", dir, ext_client_name, JackTools::GetUID(), which);
    }
}

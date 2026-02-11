CL_CURL_Debug (CURL *c, curl_infotype type, char *data, size_t size, void * ptr)
{
	if (type == CURLINFO_TEXT)
	{
		char	buff[4096];
		if (size > sizeof(buff))
			size = sizeof(buff);
		Q_strncpyz (buff, data, size);
		Com_Printf ("DEBUG: %s\n", buff);
	}

	return 0;
}

CL_HTTP_Cleanup (qboolean fullShutdown)
{
	dlhandle_t	*dl;
	int			i;

	if (fullShutdown && httpDown)
		return;

	for (i = 0; i < 4; i++)
	{
		dl = &cls.HTTPHandles[i];

		if (dl->file)
		{
			fclose (dl->file);
			remove (dl->filePath);
			dl->file = NULL;
		}

		if (dl->tempBuffer)
		{
			Z_Free (dl->tempBuffer);
			dl->tempBuffer = NULL;
		}

		if (dl->curl)
		{
			if (multi)
				curl_multi_remove_handle (multi, dl->curl);
			curl_easy_cleanup (dl->curl);
			dl->curl = NULL;
		}
	}

	if (multi)
	{
		curl_multi_cleanup (multi);
		multi = NULL;
	}

	if (fullShutdown)
	{
		curl_global_cleanup ();
		httpDown = true;
	}
}

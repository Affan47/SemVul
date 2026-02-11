ftp_exec(void *_object, int what, GB_ARRAY commands)
{
	struct curl_slist *list;
	int i;

	if (THIS_STATUS > 0)
		return 1;

	THIS->method = what == EXEC_PUT ? 1 : 0;

	ftp_initialize_curl_handle(THIS);

	switch(what)
	{
		case EXEC_GET:

			curl_easy_setopt(THIS_CURL, CURLOPT_WRITEFUNCTION , (curl_write_callback)ftp_write_curl);
			curl_easy_setopt(THIS_CURL, CURLOPT_WRITEDATA     , _object);
			curl_easy_setopt(THIS_CURL, CURLOPT_UPLOAD        , 0);

			break;

		case EXEC_PUT:

			curl_easy_setopt(THIS_CURL, CURLOPT_READFUNCTION , (curl_read_callback)ftp_read_curl);
			curl_easy_setopt(THIS_CURL, CURLOPT_READDATA     , _object);
			curl_easy_setopt(THIS_CURL, CURLOPT_UPLOAD       , 1);

			break;

		case EXEC_CMD:

			curl_easy_setopt(THIS_CURL, CURLOPT_NOBODY, 1);

			if (commands)
			{
				GB.Unref(&THIS_FTP->commands);
				THIS_FTP->commands = commands;
				GB.Ref(commands);

				list = NULL;
				for (i = 0; i < GB.Array.Count(commands); i++)
					list = curl_slist_append(list, *(char **)GB.Array.Get(commands, i));
				curl_easy_setopt(THIS_CURL, CURLOPT_QUOTE, list);
			}

			break;
	}

	if (THIS->async)
	{
		#if DEBUG
		fprintf(stderr, "-- [%p] curl_multi_add_handle(%p)\n", THIS, THIS_CURL);
		#endif
		CURL_start_post(THIS);
		return 0;
	}

	CURL_manage_error(_object, curl_easy_perform(THIS_CURL));
	return 0;
}

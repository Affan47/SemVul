CURL_manage_error(void *_object, int error)
{
	if (THIS_FILE)
	{
		fclose(THIS_FILE);
		THIS_FILE = NULL;
	}

	switch (error)
	{
		case CURLE_OK:

			if (THIS->async)
			{
				#if DEBUG
				fprintf(stderr, "-- [%p] curl_multi_remove_handle(%p)\n", THIS, THIS_CURL);
				#endif
				curl_multi_remove_handle(CCURL_multicurl,THIS_CURL);
			}
			GB.Ref(THIS);
			GB.Post(CURL_raise_finished, (intptr_t)THIS);
			CURL_stop(THIS);
			THIS_STATUS = NET_INACTIVE;
			break;

		default:

			if (THIS->async)
			{
				#if DEBUG
				fprintf(stderr, "-- [%p] curl_multi_remove_handle(%p)\n", THIS, THIS_CURL);
				#endif
				curl_multi_remove_handle(CCURL_multicurl,THIS_CURL);
			}
			GB.Ref(THIS);
			GB.Post(CURL_raise_error, (intptr_t)THIS);
			CURL_stop(THIS);
			THIS_STATUS = (- (1000 + error));
			break;
	}

	if (THIS->async)
		GB.Unref(POINTER(&_object));
}

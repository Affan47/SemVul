SetLastError(guint32 code)
{
	int ret;

	if (_wapi_has_shut_down)
		return;

	mono_once(&error_key_once, error_init);
	ret = pthread_setspecific(error_key, GUINT_TO_POINTER(code));
	g_assert (ret == 0);
}

_plug_get_error_message (const sasl_utils_t *utils,
#ifdef WIN32
				DWORD error
#else
				int error
#endif
				)
{
    char * return_value;
#ifdef WIN32
    LPVOID lpMsgBuf;

    FormatMessage(
	FORMAT_MESSAGE_ALLOCATE_BUFFER |
	FORMAT_MESSAGE_FROM_SYSTEM |
	FORMAT_MESSAGE_IGNORE_INSERTS,
	NULL,
	error,
	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	(LPTSTR) &lpMsgBuf,
	0,
	NULL
    );

    if (_plug_strdup (utils, lpMsgBuf, &return_value, NULL) != SASL_OK) {
	return_value = NULL;
    }

    LocalFree( lpMsgBuf );
#else
    if (_plug_strdup (utils, strerror(error), &return_value, NULL) != SASL_OK) {
	return_value = NULL;
    }
#endif
    return (return_value);
}

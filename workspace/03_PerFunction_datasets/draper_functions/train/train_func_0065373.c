upscli_errcheck(UPSCONN_t *ups, char *buf)
{
	int	i;

	if (!ups) {
		return -1;
	}

	if (!buf) {
		ups->upserror = UPSCLI_ERR_INVALIDARG;
		return -1;
	}


	if (strncmp(buf, "ERR", 3) != 0) {
		return 0;
	}


	for (i = 0; upsd_errlist[i].text != NULL; i++) {
		if (!strncmp(&buf[4], upsd_errlist[i].text,
			strlen(upsd_errlist[i].text))) {
			ups->upserror = upsd_errlist[i].errnum;
			return -1;
		}
	}


	ups->upserror = UPSCLI_ERR_UNKNOWN;
	return -1;
}

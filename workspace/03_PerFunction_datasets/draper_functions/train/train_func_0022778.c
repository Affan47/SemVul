mime_getcontent(char *s)
{
	if (strchr(s, '/') == NULL)
		return MIME_TEXT;
	if (asccasecmp(s, "text/plain") == 0)
		return MIME_TEXT_PLAIN;
	if (asccasecmp(s, "text/html") == 0)
		return MIME_TEXT_HTML;
	if (ascncasecmp(s, "text/", 5) == 0)
		return MIME_TEXT;
	if (asccasecmp(s, "message/rfc822") == 0)
		return MIME_822;
	if (ascncasecmp(s, "message/", 8) == 0)
		return MIME_MESSAGE;
	if (asccasecmp(s, "multipart/alternative") == 0)
		return MIME_ALTERNATIVE;
	if (asccasecmp(s, "multipart/digest") == 0)
		return MIME_DIGEST;
	if (ascncasecmp(s, "multipart/", 10) == 0)
		return MIME_MULTI;
	if (asccasecmp(s, "application/x-pkcs7-mime") == 0 ||
				asccasecmp(s, "application/pkcs7-mime") == 0)
		return MIME_PKCS7;
	return MIME_UNKNOWN;
}

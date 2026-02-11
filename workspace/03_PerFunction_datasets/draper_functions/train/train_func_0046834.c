_estrndup(const char *s, uint length ZEND_FILE_LINE_DC ZEND_FILE_LINE_ORIG_DC)
{
	char *p;

	p = (char *) _emalloc(length+1 ZEND_FILE_LINE_RELAY_CC ZEND_FILE_LINE_ORIG_RELAY_CC);
	if (UNEXPECTED(p == NULL)) {
		return p;
	}
	memcpy(p, s, length);
	p[length] = 0;
	return p;
}

rtf_to_unicode(int code) {
	int cc=code;
	if (code < 0 || (cc=to_unicode(current_charset, code)) < 0 ) return 0xFEFF;
	return cc;
}

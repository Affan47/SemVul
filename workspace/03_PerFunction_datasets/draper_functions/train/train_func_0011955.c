set_time_locale() {
	if (!runtime_locale_check) return;
	if (!locale_charset) return;
	if (strcmp(locale_charset,dest_csname)!=0) return;
	setlocale(LC_TIME,"");
}

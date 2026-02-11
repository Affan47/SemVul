gf_term_check_extension(GF_InputService *ifce, const char *mimeType, const char *extList, const char *description, const char *fileExt)
{
	const char *szExtList;
	char *ext, szExt[500];
	if (!ifce || !mimeType || !extList || !description || !fileExt) return 0;
	memset(szExt, 0, sizeof(szExt));

	if ( (strlen(fileExt)>20) || strchr(fileExt, '/')) return 0;

	if (fileExt[0]=='.') fileExt++;
	strcpy(szExt, fileExt);
	strlwr(szExt);
	ext = strchr(szExt, '#');
	if (ext) ext[0]=0;

	szExtList = gf_modules_get_option((GF_BaseInterface *)(GF_BaseInterface *)ifce, "MimeTypes", mimeType);
	if (!szExtList) {
		gf_term_register_mime_type(ifce, mimeType, extList, description);
		szExtList = gf_modules_get_option((GF_BaseInterface *)(GF_BaseInterface *)ifce, "MimeTypes", mimeType);
	}
	if (!strstr(szExtList, ifce->module_name)) return 0;
	return check_extension((char *)szExtList, szExt);
}

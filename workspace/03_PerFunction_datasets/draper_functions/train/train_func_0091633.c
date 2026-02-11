linkify_okUrl(const QString &url)
{
	if(url.at(url.length()-1) == '.')
		return FALSE;

	return TRUE;
}

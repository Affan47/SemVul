get_settings(void *_object)
{
	if (!_object)
		return QWebSettings::globalSettings();
	else
		return WEBVIEW->settings();
}

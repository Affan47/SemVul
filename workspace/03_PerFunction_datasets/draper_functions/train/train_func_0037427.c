reload()
{
	const Url currentUrl = m_currentUrl;
	if (closeFile())
	{
		saveLastInternalModifiedDateTime();
		loadUrl(currentUrl);
	}
}

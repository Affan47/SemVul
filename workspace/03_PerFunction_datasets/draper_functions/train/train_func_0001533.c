settings_free(rdpSettings* settings)
{
	if (settings != NULL)
	{
		freerdp_uniconv_free(settings->uniconv);
		xfree(settings->hostname);
		xfree(settings->username);
		xfree(settings->password);
		xfree(settings->domain);
		xfree(settings->shell);
		xfree(settings->directory);
		xfree(settings->client_dir);
		xfree(settings);
	}
}

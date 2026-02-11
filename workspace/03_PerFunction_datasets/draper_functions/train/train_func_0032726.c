convert_commit_encoding (GitgCommit  *commit,
                         gchar const *s)
{
	GitgConfig *config;
	gchar *encoding;
	gchar *ret;

	config = gitg_config_new (commit->priv->repository);
	encoding = gitg_config_get_value (config, "i18n.commitencoding");

	if (!encoding || !*encoding)
	{
		g_object_unref (config);
		g_free (encoding);

		config = gitg_config_new (NULL);

		encoding = gitg_config_get_value (config, "i18n.commitencoding");
	}

	g_object_unref (config);

	if (!encoding || !*encoding || g_ascii_strcasecmp (encoding, "UTF-8") == 0)
	{
		g_free (encoding);
		return g_strdup (s);
	}


	ret = g_convert (s, -1, encoding, "UTF-8", NULL, NULL, NULL);

	if (!ret)
	{

		ret = g_strdup (s);
	}

	g_free (encoding);
	return ret;
}

python_assist_clear_completion_cache (PythonAssist *assist)
{
	python_assist_cancel_queries (assist);
	anjuta_completion_clear (assist->priv->completion_cache);

	if (assist->priv->rope_cache)
	{
		g_string_free (assist->priv->rope_cache, TRUE);
		assist->priv->rope_cache = NULL;
	}
}

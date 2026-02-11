python_assist_get_calltip_cache (IAnjutaLanguageProvider* self,
                                 gchar* call_context,
                                 GError** e)
{
	PythonAssist* assist = PYTHON_ASSIST (self);
	if (!g_strcmp0 (call_context, assist->priv->calltip_context))
	{
		DEBUG_PRINT ("Calltip was found in the cache.");
		return assist->priv->tips;
	}
	else
	{
		DEBUG_PRINT ("Calltip is not available in the cache!");
		return NULL;
	}
}

key_new(const gchar *keyname, const gchar *cmdseq)
{
	CtrlKey	*key;

	key = g_malloc(sizeof *key);
	g_strlcpy(key->keyname, keyname, sizeof key->keyname);
	if(cmdseq != NULL)
		key->cmdseq = g_string_new(cmdseq);
	else
		key->cmdseq = NULL;

	return key;
}

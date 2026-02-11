test_server_cb (DBusGProxy *proxy,
		char *word[],
		char *word_eol[],
		guint hook_id,
		guint context_id,
		gpointer user_data)
{
	if (hook_id == server_id) {
		g_print ("message: %s\n", word_eol[0]);
	}
}

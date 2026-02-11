vte_send_cmd(const gchar *cmd)
{
	if (clean)
	{
		vf->vte_terminal_feed_child(VTE_TERMINAL(vc->vte), cmd, strlen(cmd));
		clean = TRUE;
		return TRUE;
	}
	else
		return FALSE;
}

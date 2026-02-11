vtesharp_terminal_base_commit (VteTerminal* terminal, const gchar* p0, guint p1)
{
	VteTerminalClass *klass = (VteTerminalClass *) get_threshold_class (G_OBJECT (terminal));
	if (klass->commit)
		(* klass->commit) (terminal, p0, p1);
}

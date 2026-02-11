gretl_command_hash_init (void)
{
    int i;

    ht = g_hash_table_new(g_str_hash, g_str_equal);

    for (i=0; gretl_cmds[i].cword != NULL; i++) {
	g_hash_table_insert(ht, (gpointer) gretl_cmds[i].cword,
			    GINT_TO_POINTER(gretl_cmds[i].cnum));
    }

    for (i=0; gretl_cmd_aliases[i].cword != NULL; i++) {
	g_hash_table_insert(ht, (gpointer) gretl_cmd_aliases[i].cword,
			    GINT_TO_POINTER(gretl_cmd_aliases[i].cnum));
    }
}

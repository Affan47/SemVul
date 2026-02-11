GetProcInfo(pid_t pid)
{
	return (ProcessTable
	?	g_hash_table_lookup(ProcessTable, GINT_TO_POINTER(pid))
	:	NULL);
}

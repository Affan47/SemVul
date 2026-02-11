process_del ( struct process *process ) {
	if ( ! list_empty ( &process->list ) ) {
		DBGC ( process, "PROCESS %p stopping\n", process );
		list_del ( &process->list );
		INIT_LIST_HEAD ( &process->list );
		ref_put ( process->refcnt );
	} else {
		DBGC ( process, "PROCESS %p already stopped\n", process );
	}
}

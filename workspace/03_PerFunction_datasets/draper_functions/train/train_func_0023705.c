connection_table_move_connection_on_to_active_list(Connection_Table *ct,Connection *c)
{
	PR_ASSERT(c->c_next==NULL);
	PR_ASSERT(c->c_prev==NULL);

	PR_Lock(ct->table_mutex);

	connection_acquire_nolock (c);

#ifdef FOR_DEBUGGING
    slapi_log_error(SLAPI_LOG_FATAL, "connection", "Moving connection into active list\n");
    connection_table_dump_active_connection (c);
#endif

	c->c_next = ct->c[0].c_next;
	if ( c->c_next != NULL )
	{
		c->c_next->c_prev = c;
	}
	c->c_prev = &(ct->c[0]);
	ct->c[0].c_next = c;

    PR_Unlock(ct->table_mutex);

#ifdef FOR_DEBUGGING
	connection_table_dump_active_connections (ct);
#endif
}

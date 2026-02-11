add_to_trace_list( char *trace_symb)
{
    trace_entry_t *new_t_l_entry = safe_malloc( sizeof( trace_entry_t),
        "adding to trace-list");
    new_t_l_entry->tracee = strdup( trace_symb);
    new_t_l_entry->next = NULL;

    if ( trace_list != NULL )
    {
	trace_list_last->next = new_t_l_entry;
    }else{
    trace_list = new_t_l_entry;
	tracing_symbols = TRUE;
    }
    trace_list_last = new_t_l_entry;
}

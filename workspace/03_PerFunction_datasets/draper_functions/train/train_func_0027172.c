get_first_debug_entry(void **loop_context, void **data_context,
                      netsnmp_variable_list *index,
                      netsnmp_iterator_info *data)
{
    int i;

    for (i=0; i<debug_num_tokens; i++) {

        if (dbg_tokens[i].token_name && (dbg_tokens[i].enabled != 2))
            break;
    }
    if ( i==debug_num_tokens )
        return NULL;

    snmp_set_var_value(index, dbg_tokens[i].token_name,
		       strlen(dbg_tokens[i].token_name));
    *loop_context = (void*)(intptr_t)i;
    *data_context = (void*)&dbg_tokens[i];
    return index;
}

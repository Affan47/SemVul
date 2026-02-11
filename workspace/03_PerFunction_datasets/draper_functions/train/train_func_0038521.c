announce_control_structs( int severity, char *call_cond,
				          unsigned int abs_token_limit)
{
    cstag_group_t *cs_temp = control_stack;
    while ( cs_temp != NULL )
    {
	if ( cs_temp->cs_abs_token_num < abs_token_limit )
	{
	    break;
	}
	if ( cs_temp->cs_not_dup )
	{
	    control_struct_incomplete( severity, call_cond, cs_temp );
	}
	cs_temp = cs_temp->prev;
    }
}

argument_list_pop( struct arg_list * formal, int formal_count, FRAME * frame, STACK * s )
{
    int i, j;

    for ( i = formal_count - 1; i >= 0; --i )
    {
        for ( j = formal[i].size - 1; j >= 0 ; --j )
        {
            struct argument * formal_arg = &formal[i].args[j];

            if ( formal_arg->flags == ARG_VARIADIC )
            {
                continue;
            }
            else if ( formal_arg->index != -1 )
            {
                LIST * old = stack_pop( s );
                LIST * * pos = &frame->module->fixed_variables[ formal_arg->index ];
                list_free( *pos );
                *pos = old;
            }
            else
            {
                var_set( frame->module, formal_arg->arg_name, stack_pop( s ), VAR_SET );
            }
        }
    }
}

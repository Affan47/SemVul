delete_module( module_t * m )
{

    if ( m->rules )
    {
        hashenumerate( m->rules, delete_rule_, (void *)0 );
        hash_free( m->rules );
        m->rules = 0;
    }

    if ( m->native_rules )
    {
        hashenumerate( m->native_rules, delete_native_rule, (void *)0 );
        hash_free( m->native_rules );
        m->native_rules = 0;
    }

    if ( m->variables )
    {
        var_done( m );
        m->variables = 0;
    }

    if ( m->fixed_variables )
    {
        int i;
        for ( i = 0; i < m->num_fixed_variables; ++i )
        {
            list_free( m->fixed_variables[ i ] );
        }
        BJAM_FREE( m->fixed_variables );
        m->fixed_variables = 0;
    }

    if ( m->variable_indices )
    {
        hashenumerate( m->variable_indices, &free_fixed_variable, (void *)0 );
        hash_free( m->variable_indices );
        m->variable_indices = 0;
    }

    if ( m->imported_modules )
    {
        hashenumerate( m->imported_modules, delete_imported_modules, (void *)0 );
        hash_free( m->imported_modules );
        m->imported_modules = 0;
    }
}

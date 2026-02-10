module_set_fixed_variables( struct module_t * m, int n_variables )
{

    struct hash * variable_indices;
    LIST * * fixed_variables = BJAM_MALLOC( n_variables * sizeof( LIST * ) );
    if ( m->fixed_variables )
    {
        memcpy( fixed_variables, m->fixed_variables, n_variables * sizeof( LIST * ) );
        BJAM_FREE( m->fixed_variables );
    }
    m->fixed_variables = fixed_variables;
    if ( m->class_module )
    {
        variable_indices = m->class_module->variable_indices;
    }
    else
    {
        variable_indices = m->variable_indices;
    }
    if ( variable_indices )
        hashenumerate( variable_indices, &load_fixed_variable, m );
    m->num_fixed_variables = n_variables;
}

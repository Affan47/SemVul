var_enter( struct module_t * module, OBJECT * symbol )
{
    int found;
    VARIABLE * v;
    int n;

    if ( ( n = module_get_fixed_var( module, symbol ) ) != -1 )
    {
        return &module->fixed_variables[ n ];
    }

    if ( !module->variables )
        module->variables = hashinit( sizeof( VARIABLE ), "variables" );

    v = (VARIABLE *)hash_insert( module->variables, symbol, &found );
    if ( !found )
    {
        v->symbol = object_copy( symbol );
        v->value = L0;
    }

    return &v->value;
}

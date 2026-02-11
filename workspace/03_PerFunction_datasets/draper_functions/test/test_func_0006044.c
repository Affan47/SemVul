bindmodule( OBJECT * name )
{

    if ( !name )
    {
        return &root;
    }
    else
    {
        PROFILE_ENTER( BINDMODULE );

        module_t * m;
        int found;

        if ( !module_hash )
            module_hash = hashinit( sizeof( module_t ), "modules" );

        m = (module_t *)hash_insert( module_hash, name, &found );
        if ( !found )
        {
            m->name = object_copy( name );
            m->variables = 0;
            m->variable_indices = 0;
            m->num_fixed_variables = 0;
            m->fixed_variables = 0;
            m->rules = 0;
            m->imported_modules = 0;
            m->class_module = 0;
            m->native_rules = 0;
            m->user_module = 0;
        }

        PROFILE_EXIT( BINDMODULE );

        return m;
    }
}

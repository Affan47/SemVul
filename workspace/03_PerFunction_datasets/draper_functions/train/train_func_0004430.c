make1bind( TARGET * t )
{
    if ( t->flags & T_FLAG_NOTFILE )
        return;

    pushsettings( root_module(), t->settings );
    object_free( t->boundname );
    t->boundname = search( t->name, &t->time, 0, ( t->flags & T_FLAG_ISFILE ) );
    t->binding = t->time ? T_BIND_EXISTS : T_BIND_MISSING;
    popsettings( root_module(), t->settings );
}

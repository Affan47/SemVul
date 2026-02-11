enter_rule( OBJECT * rulename, module_t * target_module )
{
    int found;
    RULE * r;

    r = (RULE *)hash_insert( demand_rules(target_module), rulename, &found );
    if ( !found )
    {
        r->name = object_copy( rulename );
        r->procedure = 0;
        r->module = 0;
        r->actions = 0;
        r->exported = 0;
        r->module = target_module;
    }
    return r;
}

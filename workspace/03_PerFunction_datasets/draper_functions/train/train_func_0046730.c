rml_oob_init(int* priority)
{
    if (init_done) {
        *priority = 1;
        return &orte_rml_oob_module.super;
    }

    *priority = 1;

    OBJ_CONSTRUCT(&orte_rml_oob_module.exceptions, opal_list_t);

    init_done = true;
    return &orte_rml_oob_module.super;
}

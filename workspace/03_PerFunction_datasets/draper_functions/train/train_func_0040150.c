pad_direct_reference(Pa_object *obj, int dim)
{
    if (obj->kind != KIND_ARRAY)
        return;
    foreach_statement_in_module(obj->module, pad_direct_reference_stm, obj);
}

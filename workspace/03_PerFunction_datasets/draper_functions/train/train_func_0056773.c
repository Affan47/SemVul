hybrid_variable_set_bool_default(HybridAccountVariable *var,
                                 gboolean               defalut_value)
{
    g_return_if_fail(VARIABLE_TYPE_BOOLEAN == var->type);

    var->bool_value = defalut_value;
}

mca_base_var_set_flag (int index, mca_base_var_flag_t flag, bool set)
{
    mca_base_var_t *var;
    int ret;

    ret = var_get (index, &var, true);
    if (OPAL_SUCCESS != ret || VAR_IS_SYNONYM(var[0])) {
        return OPAL_ERR_BAD_PARAM;
    }

    var->mbv_flags = (var->mbv_flags & ~flag) | (set ? flag : 0);


    return OPAL_SUCCESS;
}

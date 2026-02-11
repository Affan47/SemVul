lookup_value(
    var_t *var, var_parse_t *ctx,
    const char  *var_ptr, int  var_len, int var_inc, int var_idx,
    const char **val_ptr, int *val_len, int *val_size)
{
    char buf[1];
    int rc;


    rc = (*var->cb_value_fct)(var, var->cb_value_ctx,
                              var_ptr, var_len, var_inc, var_idx,
                              val_ptr, val_len, val_size);


    if (ctx->rel_lookup_flag && rc == VAR_ERR_UNDEFINED_VARIABLE) {
        ctx->rel_lookup_cnt--;
        buf[0] = EOS;
        *val_ptr  = buf;
        *val_len  = 0;
        *val_size = 0;
        return VAR_OK;
    }

    return rc;
}

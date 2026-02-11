get_func_handle_var( const type_t *iface, const var_t *func,
                                  unsigned char *explicit_fc, unsigned char *implicit_fc )
{
    const var_t *var;
    const var_list_t *args = type_get_function_args( func->type );

    *explicit_fc = *implicit_fc = 0;
    if (args) LIST_FOR_EACH_ENTRY( var, args, const var_t, entry )
    {
        if (!is_attr( var->attrs, ATTR_IN ) && is_attr( var->attrs, ATTR_OUT )) continue;
        if (type_get_type( var->type ) == TYPE_BASIC && type_basic_get_type( var->type ) == TYPE_BASIC_HANDLE)
        {
            *explicit_fc = RPC_FC_BIND_PRIMITIVE;
            return var;
        }
        if (get_explicit_generic_handle_type( var ))
        {
            *explicit_fc = RPC_FC_BIND_GENERIC;
            return var;
        }
        if (is_context_handle( var->type ))
        {
            *explicit_fc = RPC_FC_BIND_CONTEXT;
            return var;
        }
    }

    if ((var = get_attrp( iface->attrs, ATTR_IMPLICIT_HANDLE )))
    {
        if (type_get_type( var->type ) == TYPE_BASIC &&
            type_basic_get_type( var->type ) == TYPE_BASIC_HANDLE)
            *implicit_fc = RPC_FC_BIND_PRIMITIVE;
        else
            *implicit_fc = RPC_FC_BIND_GENERIC;
        return var;
    }

    *implicit_fc = RPC_FC_AUTO_HANDLE;
    return NULL;
}

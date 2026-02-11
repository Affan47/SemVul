get_pointer_fc_context( const type_t *type, const attr_list_t *attrs,
                                             enum type_context context )
{
    int pointer_fc = get_pointer_fc(type, attrs, context == TYPE_CONTEXT_TOPLEVELPARAM);

    if (pointer_fc == RPC_FC_UP && is_attr( attrs, ATTR_OUT ) &&
        context == TYPE_CONTEXT_PARAM && is_object( current_iface ))
        pointer_fc = RPC_FC_OP;

    return pointer_fc;
}

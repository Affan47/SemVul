add_interface_typeinfo(msft_typelib_t *typelib, type_t *interface)
{
    int idx = 0;
    const statement_t *stmt_func;
    type_t *ref;
    msft_typeinfo_t *msft_typeinfo;
    importinfo_t *ref_importinfo = NULL;
    int num_parents = 0, num_funcs = 0;
    type_t *inherit;
    const type_t *derived;

    if (-1 < interface->typelib_idx)
        return;

    if (!interface->details.iface)
    {
        error( "interface %s is referenced but not defined\n", interface->name );
        return;
    }

    if (is_attr(interface->attrs, ATTR_DISPINTERFACE))
        return add_dispinterface_typeinfo(typelib, interface);


    inherit = type_iface_get_inherit(interface);

    if(inherit) {
        ref_importinfo = find_importinfo(typelib, inherit->name);

        if(!ref_importinfo && type_iface_get_inherit(inherit) &&
           inherit->typelib_idx == -1)
            add_interface_typeinfo(typelib, inherit);
    }

    interface->typelib_idx = typelib->typelib_header.nrtypeinfos;
    msft_typeinfo = create_msft_typeinfo(typelib, TKIND_INTERFACE, interface->name, interface->attrs);
    msft_typeinfo->typeinfo->size = 4;
    msft_typeinfo->typeinfo->typekind |= 0x2200;

    for (derived = inherit; derived; derived = type_iface_get_inherit(derived))
        if (derived->name && !strcmp(derived->name, "IDispatch"))
            msft_typeinfo->typeinfo->flags |= 0x1000;


    if (!(msft_typeinfo->typeinfo->flags & 0x1000))
        msft_typeinfo->typeinfo->flags &= ~0x40;

    if(type_iface_get_inherit(interface))
        add_impl_type(msft_typeinfo, type_iface_get_inherit(interface),
                      ref_importinfo);


    for(ref = inherit; ref; ref = type_iface_get_inherit(ref)) {
        num_parents++;
        STATEMENTS_FOR_EACH_FUNC( stmt_func, type_iface_get_stmts(ref) ) {
            var_t *func = stmt_func->u.var;
            if (!is_local(func->attrs)) num_funcs++;
        }
    }
    msft_typeinfo->typeinfo->datatype2 = num_funcs << 16 | num_parents;
    msft_typeinfo->typeinfo->cbSizeVft = num_funcs * pointer_size;

    STATEMENTS_FOR_EACH_FUNC( stmt_func, type_iface_get_stmts(interface) ) {
        var_t *func = stmt_func->u.var;
        if(add_func_desc(msft_typeinfo, func, idx) == S_OK)
            idx++;
    }
}

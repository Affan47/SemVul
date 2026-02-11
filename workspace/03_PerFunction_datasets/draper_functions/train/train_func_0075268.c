ws_bc_add_pragma_user_agent_property_and_scheme(
    WsBc *bc,
    const unsigned char *name,
    size_t name_len,
    const unsigned char *property,
    size_t property_len,
    const unsigned char *scheme,
    size_t scheme_len)
{
    WsBcPragma *p;

    p = add_pragma(bc, WS_BC_PRAGMA_TYPE_USER_AGENT_PROPERTY_AND_SCHEME);

    if (p == NULL)
        return WS_FALSE;

    if (!ws_bc_add_const_utf8_string(bc, &p->index_1, name, name_len)
        || !ws_bc_add_const_utf8_string(bc, &p->index_2, property, property_len)
        || !ws_bc_add_const_utf8_string(bc, &p->index_3, scheme, scheme_len))
        return WS_FALSE;

    return WS_TRUE;
}

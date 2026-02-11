need_proxy(const type_t *iface)
{
    if (!is_object( iface )) return 0;
    if (is_local( iface->attrs )) return 0;
    if (is_attr( iface->attrs, ATTR_OLEAUTOMATION )) return 0;
    if (is_attr( iface->attrs, ATTR_DISPINTERFACE )) return 0;
    return 1;
}

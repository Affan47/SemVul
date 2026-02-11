set_doc_string(msft_typelib_t *typelib)
{
    char *str = get_attrp( typelib->typelib->attrs, ATTR_HELPSTRING );

    if (str)
    {
        int offset = ctl2_alloc_string(typelib, str);
        if (offset != -1) typelib->typelib_header.helpstring = offset;
    }
}

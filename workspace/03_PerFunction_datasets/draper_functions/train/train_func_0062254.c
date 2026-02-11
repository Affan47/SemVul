cib_client_delete_absolute(cib_t * cib, const char *section, xmlNode * data, int call_options)
{
    op_common(cib);
    return cib_internal_op(cib, CIB_OP_DELETE_ALT, NULL, section, data, NULL, call_options, NULL);
}

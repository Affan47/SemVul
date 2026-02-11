cib_prepare_diff(xmlNode * request, xmlNode ** data, const char **section)
{
    xmlNode *input_fragment = NULL;
    const char *update = crm_element_value(request, F_CIB_GLOBAL_UPDATE);

    *data = NULL;
    *section = NULL;

    if (crm_is_true(update)) {
        input_fragment = get_message_xml(request, F_CIB_UPDATE_DIFF);

    } else {
        input_fragment = get_message_xml(request, F_CIB_CALLDATA);
    }

    CRM_CHECK(input_fragment != NULL, crm_log_xml_warn(request, "no input"));
    *data = cib_prepare_common(input_fragment, NULL);
    return pcmk_ok;
}

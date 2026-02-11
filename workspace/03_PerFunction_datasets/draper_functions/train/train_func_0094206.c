parse_element(xmlNodePtr node, simple_binary_t **otabxml)
{
    Octstr *name;
    size_t i;
    unsigned char status_bits, ota_hex;
    int add_end_tag, syncstat;
    xmlAttrPtr attribute;


    syncstat = -1;
    if (octstr_search_char((**otabxml).binary, 0x55, 0) == 0) {
        syncstat = parse_ota_syncsettings(node, otabxml);
        if (syncstat >= 0) {
            return syncstat;
        }
    }

    name = octstr_create((char *)node->name);
    if (octstr_len(name) == 0) {
        octstr_destroy(name);
        return -1;
    }

    i = 0;
    while (i < NUMBER_OF_ELEMENTS) {
        if (octstr_case_compare(name, octstr_imm(ota_elements[i].name)) == 0)
            break;
        ++i;
    }

    status_bits = 0x00;
    ota_hex = 0x00;
    add_end_tag = 0;

    if (i != NUMBER_OF_ELEMENTS) {
        ota_hex = ota_elements[i].token;
        if ((status_bits = element_check_content(node)) > 0) {
            ota_hex = ota_hex | status_bits;
            if ((status_bits & WBXML_CONTENT_BIT) == WBXML_CONTENT_BIT)
                add_end_tag = 1;
        }
        output_char(ota_hex, otabxml);
    } else {
        warning(0, "OTA compiler: Unknown tag '%s' in OTA source", octstr_get_cstr(name));
        ota_hex = WBXML_LITERAL;
        if ((status_bits = element_check_content(node)) > 0) {
            ota_hex = ota_hex | status_bits;

            if ((status_bits & WBXML_CONTENT_BIT) == WBXML_CONTENT_BIT)
                add_end_tag = 1;
        }
        output_char(ota_hex, otabxml);
        output_octet_string(octstr_duplicate(name), otabxml);
    }

    if (node->properties != NULL) {
        attribute = node->properties;
        while (attribute != NULL) {
            parse_attribute(attribute, otabxml);
            attribute = attribute->next;
        }
        parse_end(otabxml);
    }

    octstr_destroy(name);
    return add_end_tag;
}

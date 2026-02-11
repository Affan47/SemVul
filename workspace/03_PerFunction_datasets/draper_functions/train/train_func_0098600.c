parse_struct_element(xmlDocPtr doc, xmlNodePtr node,
                                XMLRPCDocument *xrdoc, Dict *members)
{
    Octstr *name;
    size_t i;
    XMLRPCMember *member;


    if (node->name == NULL) {
        error(0, "XMLRPC: XML struct element nodes without name!");
        xrdoc->parse_status = XMLRPC_XMLPARSE_FAILED;
        xrdoc->parse_error = octstr_format("XML-RPC compiler: bad XML");
        return -1;
    }

    name = octstr_create(node->name);
    if (octstr_len(name) == 0) {
        octstr_destroy(name);
        return -1;
    }

    i = 0;
    while (i < NUMBER_OF_STRUCT_ELEMENTS) {
        if (octstr_case_compare(name, octstr_imm(struct_elements[i].name)) == 0)
            break;
        ++i;
    }
    if (i == NUMBER_OF_STRUCT_ELEMENTS) {
        xrdoc->parse_status = XMLRPC_PARSING_FAILED;
        xrdoc->parse_error = octstr_format("XML-RPC compiler: unknown tag '%s' "
                                           "in XML source at level <struct>",
                                           octstr_get_cstr(name));
        octstr_destroy(name);
        return -1;
    }
    octstr_destroy(name);


    if (i == 0) {

        member = xmlrpc_member_create();
        if (parse_member(doc, node->xmlChildrenNode, xrdoc, member) == -1) {
            xmlrpc_member_destroy(member, 1);
            return -1;
        }
        if (! dict_put_once(members, member->name, member->value)) {
            xrdoc->parse_status = XMLRPC_PARSING_FAILED;
            xrdoc->parse_error = octstr_format("XML-RPC compiler: at least two members have same name.");
            xmlrpc_member_destroy(member, 1);
            return -1;
        }
        xmlrpc_member_destroy(member, 0);
    } else {

        xrdoc->parse_status = XMLRPC_PARSING_FAILED;
        xrdoc->parse_error = octstr_format("XML-RPC compiler: bogus parsing exception in parse_struct!");
        return -1;
    }
    return 0;
}

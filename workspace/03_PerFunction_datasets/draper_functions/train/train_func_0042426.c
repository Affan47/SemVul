list_resource_operations(const char *rsc_id, const char *host_uname, gboolean active,
                         pe_working_set_t * data_set)
{
    resource_t *rsc = NULL;
    int opts = pe_print_printf | pe_print_rsconly | pe_print_suppres_nl;
    GListPtr ops = find_operations(rsc_id, host_uname, active, data_set);
    GListPtr lpc = NULL;

    for (lpc = ops; lpc != NULL; lpc = lpc->next) {
        xmlNode *xml_op = (xmlNode *) lpc->data;

        const char *op_rsc = crm_element_value(xml_op, "resource");
        const char *last = crm_element_value(xml_op, XML_RSC_OP_LAST_CHANGE);
        const char *status_s = crm_element_value(xml_op, XML_LRM_ATTR_OPSTATUS);
        const char *op_key = crm_element_value(xml_op, XML_LRM_ATTR_TASK_KEY);
        int status = crm_parse_int(status_s, "0");

        rsc = pe_find_resource(data_set->resources, op_rsc);
        if(rsc) {
            rsc->fns->print(rsc, "", opts, stdout);
        } else {
            fprintf(stdout, "Unknown resource %s", op_rsc);
        }

        fprintf(stdout, ": %s (node=%s, call=%s, rc=%s",
                op_key ? op_key : ID(xml_op),
                crm_element_value(xml_op, XML_ATTR_UNAME),
                crm_element_value(xml_op, XML_LRM_ATTR_CALLID),
                crm_element_value(xml_op, XML_LRM_ATTR_RC));
        if (last) {
            time_t run_at = crm_parse_int(last, "0");

            fprintf(stdout, ", last-rc-change=%s, exec=%sms\n",
                    ctime(&run_at), crm_element_value(xml_op, XML_RSC_OP_T_EXEC));
        }
        fprintf(stdout, "): %s\n", services_lrm_status_str(status));
    }
    return pcmk_ok;
}

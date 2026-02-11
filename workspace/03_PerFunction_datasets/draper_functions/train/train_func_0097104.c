msg_match_recv(orte_rml_posted_recv_t *rcv, bool get_all)
{
    opal_list_item_t *item, *next;
    orte_rml_recv_t *msg;
    orte_ns_cmp_bitmask_t mask = ORTE_NS_CMP_ALL | ORTE_NS_CMP_WILD;


    item = opal_list_get_first(&orte_rml_base.unmatched_msgs);
    while (item != opal_list_get_end(&orte_rml_base.unmatched_msgs)) {
        next = opal_list_get_next(item);
        msg = (orte_rml_recv_t*)item;
        opal_output_verbose(5, orte_rml_base_framework.framework_output,
                            "%s checking recv for %s against unmatched msg from %s",
                            ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                            ORTE_NAME_PRINT(&rcv->peer),
                            ORTE_NAME_PRINT(&msg->sender));


        if (OPAL_EQUAL == orte_util_compare_name_fields(mask, &msg->sender, &rcv->peer) &&
            msg->tag == rcv->tag) {
            ORTE_RML_ACTIVATE_MESSAGE(msg);
            opal_list_remove_item(&orte_rml_base.unmatched_msgs, item);
            if (!get_all) {
                break;
            }
        }
        item = next;
    }
}

orte_rml_base_open(mca_base_open_flag_t flags)
{

    OBJ_CONSTRUCT(&orte_rml_base.posted_recvs, opal_list_t);
    OBJ_CONSTRUCT(&orte_rml_base.unmatched_msgs, opal_list_t);


    return mca_base_framework_components_open(&orte_rml_base_framework, flags);
}

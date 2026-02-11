pe_fence_node(pe_working_set_t * data_set, node_t * node, const char *reason)
{
    CRM_CHECK(node, return);


    if (node->details->remote_rsc && node->details->remote_rsc->container) {
        resource_t *rsc = node->details->remote_rsc->container;
        if (is_set(rsc->flags, pe_rsc_failed) == FALSE) {
            crm_warn("Remote node %s will be fenced by recovering container resource %s",
                node->details->uname, rsc->id, reason);
            set_bit(rsc->flags, pe_rsc_failed);
        }
    } else if (node->details->unclean == FALSE) {
        if(pe_can_fence(data_set, node)) {
            crm_warn("Node %s will be fenced %s", node->details->uname, reason);
        } else {
            crm_warn("Node %s is unclean %s", node->details->uname, reason);
        }
        node->details->unclean = TRUE;
    }
}

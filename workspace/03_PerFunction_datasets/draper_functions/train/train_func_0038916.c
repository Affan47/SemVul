crm_update_peer(const char *source, unsigned int id, uint64_t born, uint64_t seen, int32_t votes,
                uint32_t children, const char *uuid, const char *uname, const char *addr,
                const char *state)
{
#if SUPPORT_PLUGIN
    gboolean addr_changed = FALSE;
    gboolean votes_changed = FALSE;
#endif
    crm_node_t *node = NULL;

    id = get_corosync_id(id, uuid);
    node = crm_get_peer(id, uname);

    CRM_ASSERT(node != NULL);

    if (node->uuid == NULL) {
        if (is_openais_cluster()) {

            crm_peer_uuid(node);

        } else if (uuid != NULL) {
            node->uuid = strdup(uuid);
        }
    }

    if (children > 0) {
        crm_update_peer_proc(source, node, children, state);
    }

    if (state != NULL) {
        crm_update_peer_state(source, node, state, seen);
    }
#if SUPPORT_HEARTBEAT
    if (born != 0) {
        node->born = born;
    }
#endif

#if SUPPORT_PLUGIN

    if (born != 0) {
        node->born = born;
    }

    if (votes > 0 && node->votes != votes) {
        votes_changed = TRUE;
        node->votes = votes;
    }

    if (addr != NULL) {
        if (node->addr == NULL || crm_str_eq(node->addr, addr, FALSE) == FALSE) {
            addr_changed = TRUE;
            free(node->addr);
            node->addr = strdup(addr);
        }
    }
    if (addr_changed || votes_changed) {
        crm_info("%s: Node %s: id=%u state=%s addr=%s%s votes=%d%s born=" U64T " seen=" U64T
                 " proc=%.32x", source, node->uname, node->id, node->state,
                 node->addr, addr_changed ? " (new)" : "", node->votes,
                 votes_changed ? " (new)" : "", node->born, node->last_seen, node->processes);
    }
#endif

    return node;
}

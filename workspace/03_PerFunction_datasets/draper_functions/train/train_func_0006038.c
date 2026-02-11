merge_duplicates(remote_fencing_op_t * op)
{
    GHashTableIter iter;
    remote_fencing_op_t *other = NULL;

    time_t now = time(NULL);

    g_hash_table_iter_init(&iter, remote_op_list);
    while (g_hash_table_iter_next(&iter, NULL, (void **)&other)) {
        crm_node_t *peer = NULL;

        if (other->state > st_exec) {

            continue;
        } else if (safe_str_neq(op->target, other->target)) {

            continue;
        } else if (safe_str_neq(op->action, other->action)) {
            crm_trace("Must be for the same action: %s vs. ", op->action, other->action);
            continue;
        } else if (safe_str_eq(op->client_name, other->client_name)) {
            crm_trace("Must be for different clients: %s", op->client_name);
            continue;
        } else if (safe_str_eq(other->target, other->originator)) {
            crm_trace("Can't be a suicide operation: %s", other->target);
            continue;
        }

        peer = crm_get_peer(0, other->originator);
        if(fencing_peer_active(peer) == FALSE) {
            crm_notice("Failing stonith action %s for node %s originating from %s@%s.%.8s: Originator is dead",
                       other->action, other->target, other->client_name, other->originator, other->id);
            other->state = st_failed;
            continue;

        } else if(other->total_timeout > 0 && now > (other->total_timeout + other->created)) {
            crm_info("Stonith action %s for node %s originating from %s@%s.%.8s is too old: %d vs. %d + %d",
                     other->action, other->target, other->client_name, other->originator, other->id,
                     now, other->created, other->total_timeout);
            continue;
        }


        other->duplicates = g_list_append(other->duplicates, op);
        if (other->total_timeout == 0) {
            crm_trace("Making a best-guess as to the timeout used");
            other->total_timeout = op->total_timeout =
                TIMEOUT_MULTIPLY_FACTOR * get_op_total_timeout(op, NULL, op->base_timeout);
        }
        crm_notice
            ("Merging stonith action %s for node %s originating from client %s.%.8s with identical request from %s@%s.%.8s (%ds)",
             op->action, op->target, op->client_name, op->id, other->client_name, other->originator,
             other->id, other->total_timeout);
        report_timeout_period(op, other->total_timeout);
        op->state = st_duplicate;
    }
}

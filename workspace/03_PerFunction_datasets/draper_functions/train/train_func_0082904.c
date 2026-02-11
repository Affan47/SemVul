stonith_choose_peer(remote_fencing_op_t * op)
{
    st_query_result_t *peer = NULL;
    const char *device = NULL;

    do {
        if (op->devices) {
            device = op->devices->data;
            crm_trace("Checking for someone to fence %s with %s", op->target,
                      (char *)op->devices->data);
        } else {
            crm_trace("Checking for someone to fence %s", op->target);
        }

        if ((peer = find_best_peer(device, op, FIND_PEER_SKIP_TARGET | FIND_PEER_VERIFIED_ONLY))) {
            return peer;
        } else if ((peer = find_best_peer(device, op, FIND_PEER_SKIP_TARGET))) {
            return peer;
        } else if ((peer = find_best_peer(device, op, FIND_PEER_TARGET_ONLY))) {
            return peer;
        }


    } while (is_set(op->call_options, st_opt_topology)
             && stonith_topology_next(op) == pcmk_ok);

    if (op->devices) {
        crm_notice("Couldn't find anyone to fence %s with %s", op->target,
                   (char *)op->devices->data);
    } else {
        crm_debug("Couldn't find anyone to fence %s", op->target);
    }

    return NULL;
}

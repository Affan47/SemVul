cancel_op(lrm_state_t * lrm_state, const char *rsc_id, const char *key, int op, gboolean remove)
{
    int rc = pcmk_ok;
    struct recurring_op_s *pending = NULL;

    CRM_CHECK(op != 0, return FALSE);
    CRM_CHECK(rsc_id != NULL, return FALSE);
    if (key == NULL) {
        key = make_stop_id(rsc_id, op);
    }
    pending = g_hash_table_lookup(lrm_state->pending_ops, key);

    if (pending) {
        if (remove && pending->remove == FALSE) {
            pending->remove = TRUE;
            crm_debug("Scheduling %s for removal", key);
        }

        if (pending->cancelled) {
            crm_debug("Operation %s already cancelled", key);
            return FALSE;
        }

        pending->cancelled = TRUE;

    } else {
        crm_info("No pending op found for %s", key);
        return FALSE;
    }

    crm_debug("Cancelling op %d for %s (%s)", op, rsc_id, key);

    rc = lrm_state_cancel(lrm_state, pending->rsc_id, pending->op_type, pending->interval);

    if (rc == pcmk_ok) {
        crm_debug("Op %d for %s (%s): cancelled", op, rsc_id, key);

    } else {
        crm_debug("Op %d for %s (%s): Nothing to cancel", op, rsc_id, key);


        return FALSE;
    }

    return TRUE;
}

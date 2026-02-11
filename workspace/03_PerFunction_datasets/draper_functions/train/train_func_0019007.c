lrm_remove_deleted_rsc(gpointer key, gpointer value, gpointer user_data)
{
    struct delete_event_s *event = user_data;
    struct pending_deletion_op_s *op = value;

    if (safe_str_eq(event->rsc, op->rsc)) {
        notify_deleted(event->lrm_state, op->input, event->rsc, event->rc);
        return TRUE;
    }
    return FALSE;
}

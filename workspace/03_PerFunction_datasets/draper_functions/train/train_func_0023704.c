glusterd_op_ac_ack_drain (glusterd_op_sm_event_t *event, void *ctx)
{
        int ret = 0;

        if (opinfo.pending_count > 0)
                opinfo.pending_count--;

        if (!opinfo.pending_count)
                ret = glusterd_op_sm_inject_event (GD_OP_EVENT_ALL_ACK, NULL);

        gf_log ("", GF_LOG_DEBUG, "Returning with %d", ret);

        return ret;
}

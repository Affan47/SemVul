send_cia_frame(t30_state_t *s)
{
    if ((test_ctrl_bit(s->far_dis_dtc_frame, 1)  ||  test_ctrl_bit(s->far_dis_dtc_frame, 3))  &&  0)
    {
        span_log(&s->logging, SPAN_LOG_FLOW, "Sending calling subscriber internet address '%s'\n", "");
        return TRUE;
    }
    return FALSE;
}

process_state_answering(t30_state_t *s, const uint8_t *msg, int len)
{
    switch (msg[2] & 0xFE)
    {
    case T30_DIS:


        span_log(&s->logging, SPAN_LOG_FLOW, "DIS/DTC before DIS\n");
        process_rx_dis_dtc(s, msg, len);
        break;
    case T30_DCS:


        span_log(&s->logging, SPAN_LOG_FLOW, "DCS before DIS\n");
        process_rx_dcs(s, msg, len);
        break;
    case T30_DCN:
        s->current_status = T30_ERR_TX_GOTDCN;
        disconnect(s);
        break;
    default:

        unexpected_final_frame(s, msg, len);
        break;
    }
}

jk_b_get_byte(jk_msg_buf_t *msg)
{
    unsigned char rc;
    if (msg->pos > msg->len) {
        return 0xFF;
    }
    rc = msg->buf[msg->pos++];

    return rc;
}

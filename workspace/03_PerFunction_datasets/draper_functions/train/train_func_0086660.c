sig_check_listen(SIGNALING_ENTITY *sig,struct atmsvc_msg *msg)
{
    return msg->type == as_okay ? 0 : msg->reply;
}

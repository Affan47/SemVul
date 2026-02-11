set_lec_id(uint16_t lec_id)
{
        struct atmlec_msg msg;

        memset(&msg, 0, sizeof(struct atmlec_msg));
        msg.type = l_set_lecid;
        msg.content.normal.flag = lec_id;
        if (msg_to_kernel(&msg, sizeof(struct atmlec_msg)) < 0) {
                diag(COMPONENT, DIAG_ERROR, "Could not tell kernel LEC_ID");
                return -1;
        }

        return 0;
}

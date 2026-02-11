get_cmsg_data_space(struct msghdr *msg, struct cmsghdr *cmsgh, size_t *space)
{
    size_t data_offset;
    char *data_ptr;

    if ((data_ptr = (char *)CMSG_DATA(cmsgh)) == NULL)
        return 0;
    data_offset = data_ptr - (char *)msg->msg_control;
    if (data_offset > msg->msg_controllen)
        return 0;
    *space = msg->msg_controllen - data_offset;
    return 1;
}

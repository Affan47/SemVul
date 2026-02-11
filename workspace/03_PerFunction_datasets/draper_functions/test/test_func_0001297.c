get_acl(int tag)
{
    if(tag == MSG_CLIENT_DLINE_ADD || tag == MSG_CLIENT_DLINE_DEL || tag == MSG_CLIENT_DLINE_LIST)
        return &dlines;
    if(tag == MSG_CLIENT_ELINE_ADD || tag == MSG_CLIENT_ELINE_DEL || tag == MSG_CLIENT_ELINE_LIST)
        return &elines;
    if(tag == MSG_CLIENT_ILINE_ADD || tag == MSG_CLIENT_ILINE_DEL || tag == MSG_CLIENT_ILINE_LIST)
        return &ilines;
    if(tag == MSG_CLIENT_CLASS_ADD || tag == MSG_CLIENT_CLASS_DEL || tag == MSG_CLIENT_CLASS_LIST)
        return &limits;
    return 0;
}

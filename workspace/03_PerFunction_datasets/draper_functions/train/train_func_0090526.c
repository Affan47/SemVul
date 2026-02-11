glusterfs_handle_rpc_msg (rpcsvc_request_t *req)
{
        int     ret = -1;
        xlator_t *this = THIS;
        GF_ASSERT (this);
        switch (req->procnum) {
        case GLUSTERD_BRICK_TERMINATE:
                ret = glusterfs_handle_terminate (req);
                break;
        case GLUSTERD_BRICK_XLATOR_INFO:
                ret = glusterfs_handle_translator_info_get (req);
                break;
        case GLUSTERD_BRICK_XLATOR_HEAL:
                ret = glusterfs_handle_translator_heal (req);
                break;
        default:
                break;
        }

        return ret;
}

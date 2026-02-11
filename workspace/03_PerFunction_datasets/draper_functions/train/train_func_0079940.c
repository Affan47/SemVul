resolve_entry_simple (call_frame_t *frame)
{
        server_state_t     *state = NULL;
        xlator_t           *this = NULL;
        server_resolve_t   *resolve = NULL;
        inode_t            *parent = NULL;
        inode_t            *inode = NULL;
        int                 ret = 0;

        state = CALL_STATE (frame);
        this  = frame->this;
        resolve = state->resolve_now;

        parent = inode_find (state->itable, resolve->pargfid);
        if (!parent) {


                resolve->op_ret   = -1;
                resolve->op_errno = ENOENT;
                ret = 1;
                goto out;
        }


        uuid_copy (state->loc_now->pargfid, resolve->pargfid);
        state->loc_now->parent = inode_ref (parent);
        state->loc_now->name = resolve->bname;

        inode = inode_grep (state->itable, parent, resolve->bname);
        if (!inode) {
                switch (resolve->type) {
                case RESOLVE_DONTCARE:
                case RESOLVE_NOT:
                        ret = 0;
                        break;
                case RESOLVE_MAY:
                        ret = 1;
                        break;
                default:
                        resolve->op_ret   = -1;
                        resolve->op_errno = ENOENT;
                        ret = 1;
                        break;
                }

                goto out;
        }

        if (resolve->type == RESOLVE_NOT) {
                gf_log (this->name, GF_LOG_DEBUG, "inode (pointer: %p gfid:%s"
                        " found for path (%s) while type is RESOLVE_NOT",
                        inode, uuid_utoa (inode->gfid), resolve->path);
                resolve->op_ret   = -1;
                resolve->op_errno = EEXIST;
                ret = -1;
                goto out;
        }

        ret = 0;

        state->loc_now->inode  = inode_ref (inode);

out:
        if (parent)
                inode_unref (parent);

        if (inode)
                inode_unref (inode);

        return ret;
}

stripe_first_rename_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                         int32_t op_ret, int32_t op_errno, struct iatt *buf,
                         struct iatt *preoldparent, struct iatt *postoldparent,
                         struct iatt *prenewparent, struct iatt *postnewparent,
                         dict_t *xdata)
{
        stripe_local_t *local = NULL;
        xlator_list_t  *trav = NULL;

        if (!this || !frame || !frame->local) {
                gf_log ("stripe", GF_LOG_DEBUG, "possible NULL deref");
                op_errno = EINVAL;
                goto unwind;
        }

        if (op_ret == -1) {
                goto unwind;
        }

        local = frame->local;
        trav = this->children;

        local->stbuf      = *buf;
        local->preparent  = *preoldparent;
        local->postparent = *postoldparent;
        local->pre_buf    = *prenewparent;
        local->post_buf   = *postnewparent;

        local->op_ret = 0;
        local->call_count--;

        trav = trav->next;
        while (trav) {
                STACK_WIND (frame, stripe_stack_rename_cbk,
                            trav->xlator, trav->xlator->fops->rename,
                            &local->loc, &local->loc2, NULL);
                trav = trav->next;
        }
        return 0;

unwind:
        STRIPE_STACK_UNWIND (rename, frame, -1, op_errno, buf, preoldparent,
                             postoldparent, prenewparent, postnewparent, NULL);
        return 0;
}

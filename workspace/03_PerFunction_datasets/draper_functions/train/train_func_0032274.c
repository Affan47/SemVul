syncop_setattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                    int op_ret, int op_errno,
                    struct iatt *preop, struct iatt *postop, dict_t *xdata)
{
        struct syncargs *args = NULL;

        args = cookie;

        args->op_ret   = op_ret;
        args->op_errno = op_errno;

        if (op_ret == 0) {
                args->iatt1  = *preop;
                args->iatt2  = *postop;
        }

        __wake (args);

        return 0;
}

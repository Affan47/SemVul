iot_removexattr_wrapper (call_frame_t *frame, xlator_t *this, loc_t *loc,
                         const char *name, dict_t *xdata)
{
        STACK_WIND (frame, iot_removexattr_cbk, FIRST_CHILD (this),
                    FIRST_CHILD (this)->fops->removexattr, loc, name, xdata);
        return 0;
}

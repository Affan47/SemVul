afr_sh_data_fxattrop_cbk (call_frame_t *frame, void *cookie,
                          xlator_t *this, int32_t op_ret, int32_t op_errno,
                          dict_t *xattr)
{
        int call_count  = -1;

        afr_sh_common_fxattrop_resp_handler (frame, cookie, this, op_ret,
                                             op_errno, xattr);

        call_count = afr_frame_return (frame);
        if (call_count == 0) {
                afr_sh_data_fstat (frame, this);
        }

        return 0;
}

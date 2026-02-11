maccomp_getxattr_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                      int32_t op_ret, int32_t op_errno, dict_t *dict)
{
        intptr_t ax = (intptr_t)this->private;
        int i = 0;

        if ((ax == GF_XATTR_ALL && op_ret >= 0) || ax != GF_XATTR_NONE) {
                op_ret = op_errno = 0;

                for (i = 0; i < GF_XATTR_ALL; i++) {
                        if (dict_get (dict, apple_xattr_name[i]))
                                continue;

                        if (dict_set (dict, apple_xattr_name[i],
                                      bin_to_data ((void *)apple_xattr_value[i],
                                                   apple_xattr_len[i])) == -1) {
                                op_ret = -1;
                                op_errno = ENOMEM;

                                break;
                        }
                }
         }

        STACK_UNWIND_STRICT (getxattr, frame, op_ret, op_errno, dict);

        return 0;
}

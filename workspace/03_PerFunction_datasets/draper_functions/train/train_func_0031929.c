dht_getxattr_unwind (call_frame_t *frame,
                     int op_ret, int op_errno, dict_t *dict, dict_t *xdata)
{
        DHT_STACK_UNWIND (getxattr, frame, op_ret, op_errno, dict, xdata);
        return 0;
}

trace_rchecksum_cbk (call_frame_t *frame, void *cookie, xlator_t *this,
                     int32_t op_ret, int32_t op_errno,
                     uint32_t weak_checksum, uint8_t *strong_checksum, dict_t *xdata)
{
        if (trace_fop_names[GF_FOP_RCHECKSUM].enabled) {
                gf_log (this->name, GF_LOG_INFO,
                        "%"PRId64": gfid=%s op_ret=%d op_errno=%d",
                        frame->root->unique, uuid_utoa (frame->local), op_ret, op_errno);
        }

        frame->local = NULL;
        STACK_UNWIND_STRICT (rchecksum, frame, op_ret, op_errno, weak_checksum,
                             strong_checksum, xdata);

        return 0;
}

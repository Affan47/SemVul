qr_readv_cbk (call_frame_t *frame, void *cookie, xlator_t *this, int32_t op_ret,
              int32_t op_errno, struct iovec *vector, int32_t count,
              struct iatt *stbuf, struct iobref *iobref)
{
        GF_ASSERT (frame);

        QR_STACK_UNWIND (readv, frame, op_ret, op_errno, vector, count,
                         stbuf, iobref);
        return 0;
}

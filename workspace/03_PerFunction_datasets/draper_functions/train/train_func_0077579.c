iot_open (call_frame_t *frame, xlator_t *this, loc_t *loc, int32_t flags,
          fd_t *fd, int32_t wbflags)
{
        call_stub_t	*stub = NULL;
        int             ret = -1;

        stub = fop_open_stub (frame, iot_open_wrapper, loc, flags, fd, wbflags);
        if (!stub) {
                gf_log (this->name, GF_LOG_ERROR,
                        "cannot create open call stub"
                        "(out of memory)");
                ret = -ENOMEM;
                goto out;
        }

	ret = iot_schedule (frame, this, stub);

out:
        if (ret < 0) {
                STACK_UNWIND_STRICT (open, frame, -1, -ret, NULL);

                if (stub != NULL) {
                        call_stub_destroy (stub);
                }
        }

	return 0;
}

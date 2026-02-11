iot_truncate (call_frame_t *frame, xlator_t *this, loc_t *loc, off_t offset,
              dict_t *xdata)
{
	call_stub_t *stub;
        int         ret = -1;

        stub = fop_truncate_stub (frame, iot_truncate_wrapper, loc, offset,
                                  xdata);
	if (!stub) {
		gf_log (this->name, GF_LOG_ERROR,
                        "cannot create fop_stat call stub"
                        "(out of memory)");
                ret = -ENOMEM;
                goto out;
	}

        ret = iot_schedule (frame, this, stub);

out:
        if (ret < 0) {
		STACK_UNWIND_STRICT (truncate, frame, -1, -ret, NULL, NULL,
                                     NULL);

                if (stub != NULL) {
                        call_stub_destroy (stub);
                }
        }

	return 0;
}

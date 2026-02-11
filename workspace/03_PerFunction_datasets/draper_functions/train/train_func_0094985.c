modify_user_hw_breakpoint(struct perf_event *bp, struct perf_event_attr *attr)
{
	u64 old_addr = bp->attr.bp_addr;
	u64 old_len = bp->attr.bp_len;
	int old_type = bp->attr.bp_type;
	int err = 0;


	if (irqs_disabled() && bp->ctx && bp->ctx->task == current)
		__perf_event_disable(bp);
	else
		perf_event_disable(bp);

	bp->attr.bp_addr = attr->bp_addr;
	bp->attr.bp_type = attr->bp_type;
	bp->attr.bp_len = attr->bp_len;

	if (attr->disabled)
		goto end;

	err = validate_hw_breakpoint(bp);
	if (!err)
		perf_event_enable(bp);

	if (err) {
		bp->attr.bp_addr = old_addr;
		bp->attr.bp_type = old_type;
		bp->attr.bp_len = old_len;
		if (!bp->attr.disabled)
			perf_event_enable(bp);

		return err;
	}

end:
	bp->attr.disabled = attr->disabled;

	return 0;
}

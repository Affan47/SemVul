gru_dump_chiplet_request(unsigned long arg)
{
	struct gru_state *gru;
	struct gru_dump_chiplet_state_req req;
	void __user *ubuf;
	void __user *ubufend;
	int ctxnum, ret, cnt = 0;

	if (copy_from_user(&req, (void __user *)arg, sizeof(req)))
		return -EFAULT;


	if (req.gid >= gru_max_gids)
		return -EINVAL;

	gru = GID_TO_GRU(req.gid);
	ubuf = req.buf;
	ubufend = req.buf + req.buflen;

	ret = gru_dump_tfm(gru, ubuf, ubufend);
	if (ret < 0)
		goto fail;
	ubuf += ret;

	ret = gru_dump_tgh(gru, ubuf, ubufend);
	if (ret < 0)
		goto fail;
	ubuf += ret;

	for (ctxnum = 0; ctxnum < GRU_NUM_CCH; ctxnum++) {
		if (req.ctxnum == ctxnum || req.ctxnum < 0) {
			ret = gru_dump_context(gru, ctxnum, ubuf, ubufend,
						req.data_opt, req.lock_cch,
						req.flush_cbrs);
			if (ret < 0)
				goto fail;
			ubuf += ret;
			cnt++;
		}
	}

	if (copy_to_user((void __user *)arg, &req, sizeof(req)))
		return -EFAULT;
	return cnt;

fail:
	return ret;
}

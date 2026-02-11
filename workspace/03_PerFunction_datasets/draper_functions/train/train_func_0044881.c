tg_set_max(struct kernfs_open_file *of,
			  char *buf, size_t nbytes, loff_t off)
{
	struct blkcg *blkcg = css_to_blkcg(of_css(of));
	struct blkg_conf_ctx ctx;
	struct throtl_grp *tg;
	u64 v[4];
	int ret;

	ret = blkg_conf_prep(blkcg, &blkcg_policy_throtl, buf, &ctx);
	if (ret)
		return ret;

	tg = blkg_to_tg(ctx.blkg);

	v[0] = tg->bps[READ];
	v[1] = tg->bps[WRITE];
	v[2] = tg->iops[READ];
	v[3] = tg->iops[WRITE];

	while (true) {
		char tok[27];
		char *p;
		u64 val = -1;
		int len;

		if (sscanf(ctx.body, "%26s%n", tok, &len) != 1)
			break;
		if (tok[0] == '\0')
			break;
		ctx.body += len;

		ret = -EINVAL;
		p = tok;
		strsep(&p, "=");
		if (!p || (sscanf(p, "%llu", &val) != 1 && strcmp(p, "max")))
			goto out_finish;

		ret = -ERANGE;
		if (!val)
			goto out_finish;

		ret = -EINVAL;
		if (!strcmp(tok, "rbps"))
			v[0] = val;
		else if (!strcmp(tok, "wbps"))
			v[1] = val;
		else if (!strcmp(tok, "riops"))
			v[2] = min_t(u64, val, UINT_MAX);
		else if (!strcmp(tok, "wiops"))
			v[3] = min_t(u64, val, UINT_MAX);
		else
			goto out_finish;
	}

	tg->bps[READ] = v[0];
	tg->bps[WRITE] = v[1];
	tg->iops[READ] = v[2];
	tg->iops[WRITE] = v[3];

	tg_conf_updated(tg);
	ret = 0;
out_finish:
	blkg_conf_finish(&ctx);
	return ret ?: nbytes;
}

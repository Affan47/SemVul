vtc_hexdump(struct vtclog *vl, unsigned lvl, const char *pfx, const unsigned char *str, int len)
{
	int nl = 1;
	unsigned l;
	double tx;

	CHECK_OBJ_NOTNULL(vl, VTCLOG_MAGIC);
	tx = TIM_mono() - t0;
	assert(len >= 0);
	assert(lvl < NLEAD);
	AZ(pthread_mutex_lock(&vl->mtx));
	VSB_clear(vl->vsb);
	if (pfx == NULL)
		pfx = "";
	if (str == NULL)
		VSB_printf(vl->vsb, "%s %-4s %4.1f %s| (null)",
		    lead[lvl], vl->id, tx, pfx);
	else {
		for (l = 0; l < len; l++, str++) {
			if (l > 512) {
				VSB_printf(vl->vsb, "...");
				break;
			}
			if (nl) {
				VSB_printf(vl->vsb, "%s %-4s %4.1f %s| ",
				    lead[lvl], vl->id, tx, pfx);
				nl = 0;
			}
			VSB_printf(vl->vsb, " %02x", *str);
			if ((l & 0xf) == 0xf) {
				VSB_printf(vl->vsb, "\n");
				nl = 1;
			}
		}
	}
	if (!nl)
		VSB_printf(vl->vsb, "\n");
	AZ(VSB_finish(vl->vsb));

	vtc_log_emit(vl, lvl);

	VSB_clear(vl->vsb);
	AZ(pthread_mutex_unlock(&vl->mtx));
	if (lvl == 0) {
		vtc_error = 1;
		if (pthread_self() != vtc_thread)
			pthread_exit(NULL);
	}
}

pvr2_hdw_state_log_state(struct pvr2_hdw *hdw)
{
	char buf[256];
	unsigned int idx, ccnt;
	unsigned int lcnt, ucnt;

	for (idx = 0; ; idx++) {
		ccnt = pvr2_hdw_report_unlocked(hdw,idx,buf,sizeof(buf));
		if (!ccnt) break;
		printk(KERN_INFO "%s %.*s\n",hdw->name,ccnt,buf);
	}
	ccnt = pvr2_hdw_report_clients(hdw, buf, sizeof(buf));
	ucnt = 0;
	while (ucnt < ccnt) {
		lcnt = 0;
		while ((lcnt + ucnt < ccnt) && (buf[lcnt + ucnt] != '\n')) {
			lcnt++;
		}
		printk(KERN_INFO "%s %.*s\n", hdw->name, lcnt, buf + ucnt);
		ucnt += lcnt + 1;
	}
}

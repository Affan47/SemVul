ng_rewind(struct irs_ng *this, const char *group) {
	struct pvt *pvt = (struct pvt *)this->private;

	if (pvt->fp != NULL && fseek(pvt->fp, SEEK_CUR, 0L) == -1) {
		fclose(pvt->fp);
		pvt->fp = NULL;
	}

	if (pvt->fp == NULL || pvt->grouphead.gr == NULL ||
	    strcmp(group, pvt->grouphead.grname)) {
		freelists(this);
		if (pvt->fp != NULL)
			fclose(pvt->fp);
		pvt->fp = fopen(_PATH_NETGROUP, "r");
		if (pvt->fp != NULL) {
			if (parse_netgrp(this, group))
				freelists(this);
			if (!(pvt->grouphead.grname = strdup(group)))
				freelists(this);
			fclose(pvt->fp);
			pvt->fp = NULL;
		}
	}
	pvt->nextgrp = pvt->grouphead.gr;
}

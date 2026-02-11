sv_close(struct irs_sv *this) {
	struct pvt *pvt = (struct pvt *)this->private;

#ifdef IRS_LCL_SV_DB
	if (pvt->dbh != NULL)
		(*pvt->dbh->close)(pvt->dbh);
#endif
	if (pvt->sv.fp)
		fclose(pvt->sv.fp);
	memput(pvt, sizeof *pvt);
	memput(this, sizeof *this);
}

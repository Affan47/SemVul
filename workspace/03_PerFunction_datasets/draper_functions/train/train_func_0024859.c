print_rds_eon(const struct v4l2_rds_eon_set *eon_set)
{
	int counter = 0;

	printf("\n\nEnhanced Other Network information: %u channels", eon_set->size);
	for (int i = 0; i < eon_set->size; i++, counter++) {
		if (eon_set->eon[i].valid_fields & V4L2_RDS_PI)
			printf("\nPI(ON %02i) =  %04x", i, eon_set->eon[i].pi);
		if (eon_set->eon[i].valid_fields & V4L2_RDS_PS)
			printf("\nPS(ON %02i) =  %s", i, eon_set->eon[i].ps);
		if (eon_set->eon[i].valid_fields & V4L2_RDS_PTY)
			printf("\nPTY(ON %02i) =  %0u", i, eon_set->eon[i].pty);
		if (eon_set->eon[i].valid_fields & V4L2_RDS_LSF)
			printf("\nLSF(ON %02i) =  %0u", i, eon_set->eon[i].lsf);
		if (eon_set->eon[i].valid_fields & V4L2_RDS_AF)
			printf("\nPTY(ON %02i) =  %0u", i, eon_set->eon[i].pty);
		if (eon_set->eon[i].valid_fields & V4L2_RDS_TP)
			printf("\nTP(ON %02i): %s", i, eon_set->eon[i].tp? "yes":"no");
		if (eon_set->eon[i].valid_fields & V4L2_RDS_TA)
			printf("\nTA(ON %02i): %s", i, eon_set->eon[i].tp? "yes":"no");
		if (eon_set->eon[i].valid_fields & V4L2_RDS_AF) {
			printf("\nAF(ON %02i): size=%i", i, eon_set->eon[i].af.size);
			print_rds_af(&(eon_set->eon[i].af));
		}
	}
}

pcgive_set_stobs_endobs (int y0, int p0, int y1, int p1,
			 SERIESINFO *sinfo)
{
    int err = 0;

    if (sinfo->pd == 1) {
	sprintf(sinfo->stobs, "%d", y0);
	sprintf(sinfo->endobs, "%d", y1);
	if (y0 == 1) {
	    sinfo->undated = 1;
	}
    } else if (sinfo->pd == 4) {
	sprintf(sinfo->stobs, "%d:%d", y0, p0);
	sprintf(sinfo->endobs, "%d:%d", y1, p1);
    } else if (sinfo->pd == 12 || sinfo->pd == 52) {
	sprintf(sinfo->stobs, "%d:%02d", y0, p0);
	sprintf(sinfo->endobs, "%d:%02d", y1, p1);
    } else {
	err = E_DATA;
    }

    return err;
}

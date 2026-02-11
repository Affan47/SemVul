db_range_check (SERIESINFO *sinfo, DATASET *dset)
{
    double sdn_orig = get_date_x(dset->pd, dset->endobs);
    double sd0 = get_date_x(sinfo->pd, sinfo->stobs);
    double sdn = get_date_x(sinfo->pd, sinfo->endobs);
    int err = 0;

    if (sd0 > sdn_orig || sdn < dset->sd0) {
	gretl_errmsg_sprintf(_("%s: observation range does not overlap\n"
			       "with the working data set"),
			     sinfo->varname);
	err = 1;
    }

    return err;
}

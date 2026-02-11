series_record_display_name (DATASET *dset, int i,
			  const char *s)
{
    char *targ = dset->varinfo[i]->display_name;

    if (strcmp(targ, s)) {
	*targ = 0;
	strncat(targ, s, MAXDISP - 1);
	set_dataset_is_changed();
    }

    return 0;
}

print_smpl (const DATASET *dset, int fulln, PRN *prn)
{
    if (!gretl_messages_on() || dset->v == 0 || gretl_looping_quietly()) {
	return;
    }

    if (fulln && !dataset_is_panel(dset)) {
	pprintf(prn, _("Full data set: %d observations\n"), fulln);
	if (sample_size(dset) < dset->n) {
	    print_sample_obs(dset, prn);
	} else {
	    pprintf(prn, _("Current sample: %d observations\n"),
		    dset->n);
	}
	return;
    }

    if (fulln) {
	pprintf(prn, _("Full data set: %d observations\n"), fulln);
    } else {
	pprintf(prn, "%s: %s - %s (n = %d)\n", _("Full data range"),
		dset->stobs, dset->endobs, dset->n);
    }

    if (dset->t1 > 0 || dset->t2 < dset->n - 1 ||
	(fulln && dataset_is_panel(dset))) {
	print_sample_obs(dset, prn);
    }

    pputc(prn, '\n');
}

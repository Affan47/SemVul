get_bkbp_periods (const DATASET *dset, int *l, int *u)
{
    *l = (dset->pd == 4)? 6 :
	(dset->pd == 12)? 18 : 2;

    *u = (dset->pd == 4)? 32 :
	(dset->pd == 12)? 96 : 8;
}

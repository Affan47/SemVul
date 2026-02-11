daio_rsc_init(struct daio *daio,
			 const struct daio_desc *desc,
			 struct hw *hw)
{
	int err;
	unsigned int idx_l, idx_r;

	switch (hw->chip_type) {
	case ATC20K1:
		idx_l = idx_20k1[desc->type].left;
		idx_r = idx_20k1[desc->type].right;
		break;
	case ATC20K2:
		idx_l = idx_20k2[desc->type].left;
		idx_r = idx_20k2[desc->type].right;
		break;
	default:
		return -EINVAL;
	}
	err = rsc_init(&daio->rscl, idx_l, DAIO, desc->msr, hw);
	if (err)
		return err;

	err = rsc_init(&daio->rscr, idx_r, DAIO, desc->msr, hw);
	if (err)
		goto error1;


	if (desc->type <= DAIO_OUT_MAX) {
		daio->rscl.ops = daio->rscr.ops = &daio_out_rsc_ops;
	} else {
		switch (hw->chip_type) {
		case ATC20K1:
			daio->rscl.ops = daio->rscr.ops = &daio_in_rsc_ops_20k1;
			break;
		case ATC20K2:
			daio->rscl.ops = daio->rscr.ops = &daio_in_rsc_ops_20k2;
			break;
		default:
			break;
		}
	}
	daio->type = desc->type;

	return 0;

error1:
	rsc_uninit(&daio->rscl);
	return err;
}

srcimp_rsc_init(struct srcimp *srcimp,
			   const struct srcimp_desc *desc,
			   struct srcimp_mgr *mgr)
{
	int err;

	err = rsc_init(&srcimp->rsc, srcimp->idx[0],
		       SRCIMP, desc->msr, mgr->mgr.hw);
	if (err)
		return err;


	srcimp->imappers = kzalloc(sizeof(struct imapper)*desc->msr,
				   GFP_KERNEL);
	if (!srcimp->imappers) {
		err = -ENOMEM;
		goto error1;
	}


	srcimp->rsc.ops = &srcimp_basic_rsc_ops;
	srcimp->ops = &srcimp_ops;
	srcimp->mgr = mgr;

	srcimp->rsc.ops->master(&srcimp->rsc);

	return 0;

error1:
	rsc_uninit(&srcimp->rsc);
	return err;
}

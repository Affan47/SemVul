knh_Object_setData(CTX ctx, kObject *o, kMap *m, kNameSpace *ns, int Checked)
{
	ksfp_t *lsfp = ctx->esp;
	knitr_t mitrbuf = K_NITR_INIT, *mitr = &mitrbuf;
	klr_setesp(ctx, lsfp+1);
	if(Checked) {
		while(m->spi->next(ctx, m->mapptr, mitr, lsfp)) {
			klr_setesp(ctx, lsfp+2);
			knh_Object_fastset(ctx, o, lsfp[0].mtd, lsfp[1].o);
			klr_setesp(ctx, lsfp+1);
		}
	}
	else {
		kclass_t cid = O_cid(o);
		while(m->spi->next(ctx, m->mapptr, mitr, lsfp)) {
			if(knh_NameSpace_dataCheck(ctx, ns, cid, lsfp)) {
				klr_setesp(ctx, lsfp+2);
				knh_Object_fastset(ctx, o, lsfp[0].mtd, lsfp[1].o);
			}
			klr_setesp(ctx, lsfp+1);
		}
	}
	klr_setesp(ctx, lsfp);
}

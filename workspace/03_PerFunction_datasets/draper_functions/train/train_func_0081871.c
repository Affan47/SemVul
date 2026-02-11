knh_Exception_addStackTrace(CTX ctx, kException *e, ksfp_t *sfp)
{
	CWB_t cwbbuf, *cwb = CWB_open0(ctx, &cwbbuf);
	kMethod *mtd = sfp[K_MTDIDX].mtdNC;
	if((mtd)->mn != MN_LAMBDA) {
		int i = 0, psize = knh_Method_psize(mtd);
		kline_t uline = knh_stack_uline(ctx, sfp);
		knh_write_uline(ctx, cwb->w, uline);
		knh_write_type(ctx, cwb->w, (mtd)->cid);
		knh_putc(ctx, cwb->w, '.');
		knh_write_mn(ctx, cwb->w, (mtd)->mn);
		knh_putc(ctx, cwb->w, '(');
		for(i = 0; i < psize; i++) {
			kparam_t *p = knh_Param_get(DP(mtd)->mp, i);
			ktype_t type = ktype_tocid(ctx, p->type, O_cid(sfp[0].o));
			if(i > 0) {
				knh_putc(ctx, cwb->w, ',');
			}
			knh_write_fn(ctx, cwb->w, p->fn);
			knh_putc(ctx, cwb->w, '=');
			knh_write_sfp(ctx, cwb->w, type, &sfp[i+1], FMT_line);
		}
		knh_putc(ctx, cwb->w, ')');
		if(e->tracesNULL == NULL) {
			KNH_INITv(e->tracesNULL, new_Array(ctx, CLASS_String, 0));
		}
		knh_Array_add(ctx, e->tracesNULL, CWB_newString0(ctx, cwb));
	}
}

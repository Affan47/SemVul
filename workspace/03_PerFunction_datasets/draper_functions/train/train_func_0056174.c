ObjectField_getkey(CTX ctx, ksfp_t *sfp)
{
	int keyidx = O_cTBL(sfp[0].o)->keyidx;
	if(keyidx != -1) {
		kObject *of = (kObject*)sfp[0].o;
		DBG_ASSERT(IS_bString(of->fields[keyidx]));
		return (kString*)of->fields[keyidx];
	}
	return DEFAULT_getkey(ctx, sfp);
}

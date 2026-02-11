isCalledMethod(CTX ctx, ksfp_t *sfp)
{
	kMethod *mtd = sfp[0].mtdNC;
	if(knh_isObject(ctx, UPCAST(mtd)) && IS_Method(mtd)) {

		return 1;
	}
	return 0;
}

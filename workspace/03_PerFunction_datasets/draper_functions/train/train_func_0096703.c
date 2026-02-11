knh_getcid(CTX ctx, kbytes_t lname)
{
	const knh_ClassTBL_t *ct = (const knh_ClassTBL_t *)knh_DictSet_get(ctx, ctx->share->classNameDictSet, lname);
	if(ct != NULL) return ct->cid;
#if defined(K_USING_SEMANTICS)
	if(lname.buf[lname.len-1] == '}') {
		return knh_findcidx(ctx, lname);
	}
#endif
	return CLASS_unknown;
}

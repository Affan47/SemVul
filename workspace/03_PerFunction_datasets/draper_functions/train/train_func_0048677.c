Class_getNullValue(CTX ctx, ksfp_t *sfp _RIX) {
	kClass *c = sfp[0].c;
	RETURN_(KNH_NULVAL(c->cid));
}

THROW_TypeError(CTX ctx, ksfp_t *sfp, ktype_t reqt, ktype_t type)
{
	KNH_NTHROW2(ctx, sfp, "Script!!: Type Error", "konoha:type", K_FAILED, KNH_LDATA(LOG_t("requested_type", reqt), LOG_t("given_type", type)));
}

Lang_newBlock(CTX ctx, ksfp_t *sfp _RIX)
{
	kLang *lang = ctx->share->corelang;
	kline_t uline = sfp[2].ivalue == 0 ? 1 : (kline_t)sfp[2].ivalue;
	GCRETURN_(new_BlockTEXT(ctx, lang, sfp[3].ns, S_totext(sfp[1].s), uline));
}

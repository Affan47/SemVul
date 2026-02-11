knh_addConvDPI(CTX ctx, const char *scheme, const knh_ConverterDPI_t *conv, const knh_ConverterDPI_t *rconv)
{
	knh_DictSet_set(ctx, ctx->share->convDpiDictSet, new_T(scheme), (kuintptr_t)conv);
	if(rconv != NULL) {
		knh_DictSet_set(ctx, ctx->share->convDpiDictSet, new_T(scheme), (kuintptr_t)rconv);
	}
}

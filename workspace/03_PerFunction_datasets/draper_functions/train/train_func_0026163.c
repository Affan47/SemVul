knh_getURN(CTX ctx, kuri_t uri)
{
	size_t n = URI_UNMASK(uri);
	kArray *a = ctx->share->urns;
	if(n < knh_Array_size(a)) {
		return (kString*)(a)->list[n];
	}
	else {
		DBG_ASSERT(uri == URI_unknown);
		return TS_EMPTY;
	}
}

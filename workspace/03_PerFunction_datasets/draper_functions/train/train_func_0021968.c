knh_Bytes_expands(CTX ctx, kBytes *ba, size_t newsize)
{
	if(ba->dim->capacity == 0) {
		newsize = k_goodsize(newsize);
		ba->bu.ubuf = (kchar_t*)KNH_MALLOC(ctx, newsize);
		ba->dim = new_dim(ctx, newsize, 1);
	}
	else {
		kchar_t *ubuf = ba->bu.ubuf;
		ba->bu.ubuf = (kchar_t*)KNH_REALLOC(ctx, ba->DBG_name, ba->bu.ubuf, ba->dim->capacity, newsize, 1);
		((kdim_t*)ba->dim)->capacity = newsize;
		if(unlikely(ctx->bufa == ba)) {
			Bytes_checkstack(ctx, ubuf, ubuf + ba->bu.len, ba->bu.ubuf);
		}
	}
}

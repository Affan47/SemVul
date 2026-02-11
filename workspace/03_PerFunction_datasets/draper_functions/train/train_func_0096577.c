CopyHistinfo(struct histinfo *src, struct histinfo *dst)
{


    memcpy((char *)dst, (char *)src, sizeof(struct histinfo));
    dst->md_bins = NULL;
    dst->md_min = NULL;
    dst->md_max = NULL;
    dst->md_inoutlo = NULL;
    dst->md_inouthi = NULL;
    dst->md_median = NULL;

    if (src->md_bins) {
	dst->md_bins = (int *)DXAllocate(src->dim * sizeof(int));
	if (!dst->md_bins)
	    goto error;
	memcpy(dst->md_bins, src->md_bins, src->dim * sizeof(int));
    }
    if (src->md_min) {
	dst->md_min = (float *)DXAllocate(src->dim * sizeof(float));
	if (!dst->md_min)
	    goto error;
	memcpy(dst->md_min, src->md_min, src->dim * sizeof(float));
    }
    if (src->md_max) {
	dst->md_max = (float *)DXAllocate(src->dim * sizeof(float));
	if (!dst->md_max)
	    goto error;
	memcpy(dst->md_max, src->md_max, src->dim * sizeof(float));
    }
    if (src->md_inoutlo) {
	dst->md_inoutlo = (int *)DXAllocate(src->dim * sizeof(int));
	if (!dst->md_inoutlo)
	    goto error;
	memcpy(dst->md_inoutlo, src->md_inoutlo, src->dim * sizeof(int));
    }
    if (src->md_inouthi) {
	dst->md_inouthi = (int *)DXAllocate(src->dim * sizeof(int));
	if (!dst->md_inouthi)
	    goto error;
	memcpy(dst->md_inouthi, src->md_inouthi, src->dim * sizeof(int));
    }
    if (src->md_median) {
	dst->md_median = (float *)DXAllocate(src->dim * sizeof(float));
	if (!dst->md_median)
	    goto error;
	memcpy(dst->md_median, src->md_median, src->dim * sizeof(float));
    }
    return OK;

  error:
    FreeHistinfo(dst);
    return ERROR;
}

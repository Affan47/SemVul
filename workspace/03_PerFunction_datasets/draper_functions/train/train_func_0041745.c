rle_swap_0_255(grs_bitmap *bmp)
{
	int i, j, len, rle_big;
	unsigned char *ptr, *ptr2, *temp, *start;
	unsigned short line_size;

	rle_big = bmp->bm_flags & BM_FLAG_RLE_BIG;

	temp = d_malloc( MAX_BMP_SIZE(bmp->bm_w, bmp->bm_h) );

	if (rle_big) {
		ptr = bmp->bm_data + 4 + 2 * bmp->bm_h;
		ptr2 = temp + 4 + 2 * bmp->bm_h;
	} else {
		ptr = bmp->bm_data + 4 + bmp->bm_h;
		ptr2 = temp + 4 + bmp->bm_h;
	}
	for (i = 0; i < bmp->bm_h; i++) {
		start = ptr2;
		if (rle_big)
			line_size = INTEL_SHORT(*((unsigned short *)&bmp->bm_data[4 + 2 * i]));
		else
			line_size = bmp->bm_data[4 + i];
		for (j = 0; j < line_size; j++) {
			if ( ! IS_RLE_CODE(ptr[j]) ) {
				if (ptr[j] == 0) {
					*ptr2++ = RLE_CODE | 1;
					*ptr2++ = 255;
				} else
					*ptr2++ = ptr[j];
			} else {
				*ptr2++ = ptr[j];
				if ((ptr[j] & NOT_RLE_CODE) == 0)
					break;
				j++;
				if (ptr[j] == 0)
					*ptr2++ = 255;
				else if (ptr[j] == 255)
					*ptr2++ = 0;
				else
					*ptr2++ = ptr[j];
			}
		}
		if (rle_big)
			*((unsigned short *)&temp[4 + 2 * i]) = INTEL_SHORT(ptr2 - start);
		else
			temp[4 + i] = ptr2 - start;
		ptr += line_size;
	}
	len = ptr2 - temp;
	*((int *)temp) = len;
	memcpy(bmp->bm_data, temp, len);
	d_free(temp);
}

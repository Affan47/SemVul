CombineSameType(FIBITMAP *dst_dib, FIBITMAP *src_dib, unsigned x, unsigned y) {

	if(FreeImage_GetImageType(dst_dib) != FreeImage_GetImageType(src_dib)) {
		return FALSE;
	}

	unsigned src_width  = FreeImage_GetWidth(src_dib);
	unsigned src_height = FreeImage_GetHeight(src_dib);
	unsigned src_pitch  = FreeImage_GetPitch(src_dib);
	unsigned src_line   = FreeImage_GetLine(src_dib);
	unsigned dst_width  = FreeImage_GetWidth(dst_dib);
	unsigned dst_height = FreeImage_GetHeight(dst_dib);
	unsigned dst_pitch  = FreeImage_GetPitch(dst_dib);


	if((x + src_width > dst_width) || (y + src_height > dst_height)) {
		return FALSE;
	}

	BYTE *dst_bits = FreeImage_GetBits(dst_dib) + ((dst_height - src_height - y) * dst_pitch) + (x * (src_line / src_width));
	BYTE *src_bits = FreeImage_GetBits(src_dib);


	for(unsigned rows = 0; rows < src_height; rows++) {
		memcpy(dst_bits, src_bits, src_line);

		dst_bits += dst_pitch;
		src_bits += src_pitch;
	}

	return TRUE;
}

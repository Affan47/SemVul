filter_bitmap(struct mame_bitmap *bitmap, int mask)
{
	int dst_pitch;

	DWORD *pal_ptr, *edi;
	int esi, eax, ebx, ecx, edx;

	pal_ptr = internal_palette;
	esi = mask | 0xffffff00;
	edi = (DWORD*)((WORD*)bitmap->line[VIS_MINY] + VIS_MINX + CLIP_W);
	dst_pitch = bitmap->rowpixels >> 1;
	ecx = -(CLIP_W>>1);
	edx = CLIP_H;

	do {
		do {
			eax = edi[ecx];
			if (eax & 0x00ff00ff)
			{
				ebx = eax;
				eax >>= 16;
				ebx &= 0xffff;
				eax = pal_ptr[eax];
				ebx = pal_ptr[ebx];
				eax &= esi;
				ebx &= esi;
				eax <<= 16;
				ebx |= eax;
				edi[ecx] = ebx;
			}
		}
		while (++ecx);

		ecx = -(CLIP_W>>1);
		edi += dst_pitch;
	}
	while (--edx);
}

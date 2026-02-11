_SDL_gfxBlitBlitterRGBA(SDL_gfxBlitInfo * info)
{
	int       width = info->d_width;
	int       height = info->d_height;
	Uint8    *src = info->s_pixels;
	int       srcskip = info->s_skip;
	Uint8    *dst = info->d_pixels;
	int       dstskip = info->d_skip;
	SDL_PixelFormat *srcfmt = info->src;
	SDL_PixelFormat *dstfmt = info->dst;
	Uint8       srcbpp = srcfmt->BytesPerPixel;
	Uint8       dstbpp = dstfmt->BytesPerPixel;

	while (height--) {
		GFX_DUFFS_LOOP4( {
			Uint32 pixel;
			unsigned sR;
			unsigned sG;
			unsigned sB;
			unsigned sA;
			unsigned dR;
			unsigned dG;
			unsigned dB;
			unsigned dA;
			unsigned sAA;
			GFX_DISASSEMBLE_RGBA(src, srcbpp, srcfmt, pixel, sR, sG, sB, sA);
			GFX_DISASSEMBLE_RGBA(dst, dstbpp, dstfmt, pixel, dR, dG, dB, dA);
			sAA=GFX_ALPHA_ADJUST_ARRAY[sA & 255];
			GFX_ALPHA_BLEND(sR, sG, sB, sAA, dR, dG, dB);
			dA |= sAA;
			GFX_ASSEMBLE_RGBA(dst, dstbpp, dstfmt, dR, dG, dB, dA);
			src += srcbpp; dst += dstbpp;
		}, width);
		src += srcskip;
		dst += dstskip;
	}
}

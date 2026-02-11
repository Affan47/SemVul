zoomSurface(SDL_Surface * src, double zoomx, double zoomy, int smooth)
{
	SDL_Surface *rz_src;
	SDL_Surface *rz_dst;
	int dstwidth, dstheight;
	int is32bit;
	int i, src_converted;
	int flipx, flipy;


	if (src == NULL)
		return (NULL);


	is32bit = (src->format->BitsPerPixel == 32);
	if ((is32bit) || (src->format->BitsPerPixel == 8)) {


		rz_src = src;
		src_converted = 0;
	} else {


		rz_src =
			SDL_CreateRGBSurface(SDL_SWSURFACE, src->w, src->h, 32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
			0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000
#else
			0xff000000,  0x00ff0000, 0x0000ff00, 0x000000ff
#endif
			);
		if (rz_src == NULL) {
			return NULL;
		}
		SDL_BlitSurface(src, NULL, rz_src, NULL);
		src_converted = 1;
		is32bit = 1;
	}

	flipx = (zoomx<0.0);
	if (flipx) zoomx = -zoomx;
	flipy = (zoomy<0.0);
	if (flipy) zoomy = -zoomy;


	zoomSurfaceSize(rz_src->w, rz_src->h, zoomx, zoomy, &dstwidth, &dstheight);


	rz_dst = NULL;
	if (is32bit) {


		rz_dst =
			SDL_CreateRGBSurface(SDL_SWSURFACE, dstwidth, dstheight + GUARD_ROWS, 32,
			rz_src->format->Rmask, rz_src->format->Gmask,
			rz_src->format->Bmask, rz_src->format->Amask);
	} else {


		rz_dst = SDL_CreateRGBSurface(SDL_SWSURFACE, dstwidth, dstheight + GUARD_ROWS, 8, 0, 0, 0, 0);
	}


	if (rz_dst == NULL) {


		if (src_converted) {
			SDL_FreeSurface(rz_src);
		}
		return NULL;
	}


	rz_dst->h = dstheight;


	if (SDL_MUSTLOCK(rz_src)) {
		SDL_LockSurface(rz_src);
	}


	if (is32bit) {


		_zoomSurfaceRGBA(rz_src, rz_dst, flipx, flipy, smooth);


		SDL_SetAlpha(rz_dst, SDL_SRCALPHA, 255);
	} else {


		for (i = 0; i < rz_src->format->palette->ncolors; i++) {
			rz_dst->format->palette->colors[i] = rz_src->format->palette->colors[i];
		}
		rz_dst->format->palette->ncolors = rz_src->format->palette->ncolors;


		_zoomSurfaceY(rz_src, rz_dst, flipx, flipy);
		SDL_SetColorKey(rz_dst, SDL_SRCCOLORKEY | SDL_RLEACCEL, _colorkey(rz_src));
	}


	if (SDL_MUSTLOCK(rz_src)) {
		SDL_UnlockSurface(rz_src);
	}


	if (src_converted) {
		SDL_FreeSurface(rz_src);
	}


	return (rz_dst);
}

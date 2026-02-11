Draw9Tile(SDL_Surface* src, const PG_Rect& r, SDL_Surface* dst, Uint8 blend = 0) {
	PG_Rect srcrect;
	PG_Rect dstrect;
	int i = 0;


	SDL_Surface* src_stripe[3];
	int h_src_stripe = src->h / 3;


	dstrect.SetRect(0, 0, src->w, h_src_stripe);
	for(i=0; i<3; i++) {

		srcrect.SetRect(0, i*h_src_stripe, src->w, h_src_stripe);


		src_stripe[i] = SDL_CreateRGBSurface(
		                    SDL_SWSURFACE,
		                    srcrect.w,
		                    srcrect.h,
		                    32,
		                    0,
		                    0,
		                    0,
		                    0
		                );


		PG_Draw::BlitSurface(src, srcrect, src_stripe[i], dstrect);
	}


	SDL_Surface* dst_stripe[3];
	int h_dst_stripe = src->h / 3;


	dstrect.SetRect(0, 0, r.w, h_dst_stripe);
	for(i=0; i<3; i++) {

		dst_stripe[i] = SDL_CreateRGBSurface(
		                    SDL_SWSURFACE,
		                    dstrect.w,
		                    dstrect.h,
		                    32,
		                    0,
		                    0,
		                    0,
		                    0
		                );


		Draw3TileH(src_stripe[i], dstrect, dst_stripe[i], blend);


	}


	srcrect.SetRect(0, 0, dst_stripe[0]->w, dst_stripe[0]->h);
	dstrect.SetRect(r.x, r.y, r.w, dst_stripe[0]->h);
	PG_Draw::BlitSurface(dst_stripe[0], srcrect, dst, dstrect);


	dstrect.SetRect(r.x, r.y + dst_stripe[0]->h, r.w, r.h - 2*dst_stripe[0]->h);
	DrawTileSurface(dst_stripe[1], dstrect, dst, blend);


	srcrect.SetRect(0, 0, dst_stripe[2]->w, dst_stripe[2]->h);
	dstrect.SetRect(r.x, r.y+r.h-dst_stripe[2]->h, r.w, dst_stripe[2]->h);
	PG_Draw::BlitSurface(dst_stripe[2], srcrect, dst, dstrect);


	for(i=0; i<3; i++) {
		SDL_FreeSurface(src_stripe[i]);
		SDL_FreeSurface(dst_stripe[i]);
	}

}

AG_NormalizeSurfacesToDisplayFormat( AG_Frame* frames, int nFrames )
{
	int n = 0;

	if ( nFrames > 0 && frames && frames[0].surface )
	{
#if SDL_VERSION_ATLEAST(2,0,0)
		SDL_Surface* mainSurface;
		int newDispose;
		if (SDL_GetColorKey(frames[0].surface, NULL) == 0) {
			mainSurface = SDL_DisplayFormatAlpha(frames[0].surface);
			newDispose = AG_DISPOSE_RESTORE_BACKGROUND;
		} else {
			mainSurface = SDL_DisplayFormat(frames[0].surface);
			newDispose = AG_DISPOSE_NONE;
		}
#else
		SDL_Surface* mainSurface = (frames[0].surface->flags & SDL_SRCCOLORKEY) ? SDL_DisplayFormatAlpha(frames[0].surface) : SDL_DisplayFormat(frames[0].surface);
		const int newDispose = (frames[0].surface->flags & SDL_SRCCOLORKEY) ? AG_DISPOSE_RESTORE_BACKGROUND : AG_DISPOSE_NONE;
#endif
		if ( mainSurface )
		{
			int i;
			int lastDispose = AG_DISPOSE_NA;
			int iRestore = 0;
			const Uint8 alpha = (frames[0].disposal == AG_DISPOSE_NONE ||
				frames[0].disposal == AG_DISPOSE_NA) ? SDL_ALPHA_OPAQUE : SDL_ALPHA_TRANSPARENT;

			SDL_FillRect( mainSurface, NULL, SDL_MapRGBA(mainSurface->format,0,0,0,alpha) );

			for ( i = 0; i < nFrames; i++ )
			{
				if ( frames[i].surface )
				{
					SDL_Surface* surface = SDL_ConvertSurface( mainSurface, mainSurface->format, mainSurface->flags );

					if ( surface )
					{
						SDL_Rect r;

						if ( lastDispose == AG_DISPOSE_NONE )
							SDL_BlitSurface( frames[i-1].surface, NULL, surface, NULL );

						if ( lastDispose == AG_DISPOSE_RESTORE_PREVIOUS )
							SDL_BlitSurface( frames[iRestore].surface, NULL, surface, NULL );
						if ( frames[i].disposal != AG_DISPOSE_RESTORE_PREVIOUS )
							iRestore = i;

						r.x = (Sint16)frames[i].x;
						r.y = (Sint16)frames[i].y;
						SDL_BlitSurface( frames[i].surface, NULL, surface, &r );

						SDL_FreeSurface( frames[i].surface );
						frames[i].surface = surface;
						frames[i].x = frames[i].y = 0;
						lastDispose = frames[i].disposal;
						frames[i].disposal = newDispose;
						n++;
					}
				}
			}

			SDL_FreeSurface( mainSurface );
		}
	}

	return n;
}

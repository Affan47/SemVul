AG_ConvertSurfacesToDisplayFormat( AG_Frame* frames, int nFrames )
{
	int i;
	int n = 0;

	if ( frames )
	{
		for ( i = 0; i < nFrames; i++ )
		{
			if ( frames[i].surface )
			{
#if SDL_VERSION_ATLEAST(2,0,0)
				SDL_Surface* surface;
				if (SDL_GetColorKey(frames[i].surface, NULL) == 0)
					surface = SDL_DisplayFormatAlpha(frames[i].surface);
				else
					surface = SDL_DisplayFormat(frames[i].surface);
#else
				SDL_Surface* surface = (frames[i].surface->flags & SDL_SRCCOLORKEY) ? SDL_DisplayFormatAlpha(frames[i].surface) : SDL_DisplayFormat(frames[i].surface);
#endif
				if ( surface )
				{
					SDL_FreeSurface( frames[i].surface );
					frames[i].surface = surface;
					n++;
				}
			}
		}
	}

	return n;
}

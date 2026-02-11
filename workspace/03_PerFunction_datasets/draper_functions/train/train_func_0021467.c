toggle_fullscreen() {
        Uint32 flags;
        int w, h, bpp;

	SDL_Surface *surf = scaled_surface&&surface==unscaled_surface?scaled_surface:surface;

        w = unscaled_surface->w;
        h = unscaled_surface->h;
        bpp = surf->format->BitsPerPixel;

        if ( fullscreen ) {
		cout << "Switching to windowed mode."<<endl;
                flags = surf->flags & ~SDL_FULLSCREEN;
        } else {
		cout << "Switching to fullscreen mode."<<endl;
                flags = surf->flags | SDL_FULLSCREEN;
        }

        if ( SDL_VideoModeOK(w, h, bpp, flags) )
		{
		free_surface();
		fullscreen = !fullscreen;
		create_surface(w, h);
		}
}

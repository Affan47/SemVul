write_subimage(const char *fpath, SDL_Rect *subimage_rect, int x_offset, int y_offset, SDL_Surface *atlas_surface)
{
	SDL_PixelFormat *atlas_pf = atlas_surface->format;
	SDL_Surface *subimage = SDL_CreateRGBSurface(0, subimage_rect->w, subimage_rect->h, 32,
		atlas_pf->Rmask, atlas_pf->Gmask, atlas_pf->Bmask, atlas_pf->Amask);
	SDL_BlitSurface(atlas_surface, subimage_rect, subimage, NULL);

	png_save_surface(fpath, subimage);

	SDL_FreeSurface(subimage);


	char basename[4096];
	strcpy(basename, fpath);
	char *ext = strstr(basename, ".png");
	if (ext)
		*ext = '\0';
	write_offset_file(basename, x_offset, y_offset);
}

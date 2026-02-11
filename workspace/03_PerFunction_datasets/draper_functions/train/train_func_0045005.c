theme_load_font_fixed( char *name, int start, int len, int width )
{
    struct stat filestat;
    StkFont *font = 0;
    sprintf( theme_path, "%s/%s", theme_dir, name );
    if ( stat( theme_path, &filestat ) == -1 ||
         ( font = stk_font_load( SDL_SWSURFACE | SDL_NONFATAL, theme_path ) ) == 0 )
        font = stk_font_load( SDL_SWSURFACE, name );
    if ( font )
        SDL_SetColorKey( font->surface, SDL_SRCCOLORKEY,
            stk_surface_get_pixel( font->surface, 0,0 ) );
    return font;
}

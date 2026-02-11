render (const char *str)
{
    SDL_Surface *s = 0;
    SDL_Color bgcolor = { 0, 0, 0, 0 };

    s = TTF_RenderUTF8_Shaded (font, str, fgcolor, bgcolor);
    if (s) {
        SDL_SetColorKey (s, SDL_SRCCOLORKEY,0);
        return Surface::make_surface (s);
    }
    return MakeSurface(0, get_height(), 16);
}

es_ttf_renderGlyphSolid(sdl_data *sd, int len, char *buff)
{
    char *bp, *start;
    Uint16 ch;
    int sendlen;
    TTF_Font *font;
    SDL_Surface *surface;
    SDL_Color fgcolor;
    bp = buff;


    POPGLPTR(font, bp);
    fgcolor.r = get8(bp);
    fgcolor.g = get8(bp);
    fgcolor.b = get8(bp);
    ch = get16be(bp);


    surface = TTF_RenderGlyph_Solid(font, ch, fgcolor);


    bp = start = sdl_get_temp_buff(sd, 8);
    PUSHGLPTR(surface, bp);
    sendlen = bp - start;
    sdl_send(sd, sendlen);
}

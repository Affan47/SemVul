es_getPixelFormat(sdl_data *sd, int len, char * buff)
{
    char *bp, *start;
    int sendlen;
    SDL_Surface * sptr;
    SDL_PixelFormat *format;

    bp = buff;

    POPGLPTR(sptr, bp);
    if(sptr == NULL)
       error();
    format = sptr->format;
    if(format == NULL)
       error();

    bp = start = sdl_get_temp_buff(sd, 8+5*4+11);
    PUSHGLPTR(format->palette, bp);
    put8(bp, format->BitsPerPixel);
    put8(bp, format->BytesPerPixel);
    put8(bp, format->Rloss);
    put8(bp, format->Gloss);
    put8(bp, format->Bloss);
    put8(bp, format->Aloss);
    put8(bp, format->Rshift);
    put8(bp, format->Gshift);
    put8(bp, format->Bshift);
    put8(bp, format->Ashift);
    put32be(bp, format->Rmask);
    put32be(bp, format->Gmask);
    put32be(bp, format->Bmask);
    put32be(bp, format->Amask);
    put32be(bp, format->colorkey);
    put8(bp, format->alpha);

    sendlen = bp - start;
    sdl_send(sd, sendlen);
}

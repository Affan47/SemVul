AdjustSDLPalette(void)
{
    int i;

    for(i=0;i<32;i++) {
#ifdef IPHONE
        int r = (palette16[i] >> 11) * 2 / 3,
            g = ((palette16[i] >> 6) & 0x3f) * 2 / 3,
            b = (palette16[i] & 0x1f) * 2 / 3;

        palette16[224 + i] = (r << 11) | (g << 5) | b;
#endif
        SDL_palette[224+i].r=SDL_palette[i].r*2/3;
        SDL_palette[224+i].g=SDL_palette[i].g*2/3;
        SDL_palette[224+i].b=SDL_palette[i].b*2/3;
    }
#ifndef IPHONE
    SDL_SetColors(screen,SDL_palette,0,256);
#endif
}

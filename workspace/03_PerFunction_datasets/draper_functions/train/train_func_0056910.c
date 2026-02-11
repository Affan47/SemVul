loadGraphicResources (void)
{


    m_Background.reset (Surface::fromScreen ());
    SDL_Surface *blackBox =
        SDL_CreateRGBSurface (SDL_SWSURFACE | SDL_SRCALPHA,
                              m_Background->getWidth (),
                              m_Background->getHeight (),
                              m_Background->toSDLSurface ()->format->BitsPerPixel,
                              m_Background->toSDLSurface ()->format->Rmask,
                              m_Background->toSDLSurface ()->format->Gmask,
                              m_Background->toSDLSurface ()->format->Bmask,
                              m_Background->toSDLSurface ()->format->Amask);
    SDL_FillRect (blackBox, NULL, SDL_MapRGB (blackBox->format, 0, 0, 0));
    SDL_SetAlpha (blackBox, SDL_SRCALPHA, 128);
    SDL_BlitSurface (blackBox, NULL, m_Background->toSDLSurface (), NULL);


    m_Font.reset (Font::fromFile (File::getFontFilePath ("fontMenu")));
    m_FontSelected.reset (
            Font::fromFile (File::getFontFilePath ("fontMenuSelected")));
}

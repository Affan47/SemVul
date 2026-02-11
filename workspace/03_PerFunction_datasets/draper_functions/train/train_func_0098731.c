activate (void)
{
    m_Background.reset (Surface::fromScreen ());
    SDL_Rect region;
    region.x = 0;
    region.y = 0;
    region.w = m_Background->getWidth ();
    region.h = m_Background->getHeight ();
    m_ActiveState->redrawBackground (&region, m_Background->toSDLSurface ());

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

    std::auto_ptr<Font> font (Font::fromFile (File::getFontFilePath ("fontMenu")));
    font->write ("there was an error setting the video mode",
                 m_Background->getHeight () / 2 - 3 * font->getHeight (),
                 m_Background->toSDLSurface ());
    font->write ("the default settings have been set",
                 m_Background->getHeight () / 2 - 2 * font->getHeight (),
                 m_Background->toSDLSurface ());
    font->write ("press any key to continue",
                 m_Background->getHeight () / 2 + font->getHeight (),
                 m_Background->toSDLSurface ());
}

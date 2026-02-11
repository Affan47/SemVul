unlock() {
    if (SDL_MUSTLOCK (m_surface))
        SDL_UnlockSurface (m_surface);
}

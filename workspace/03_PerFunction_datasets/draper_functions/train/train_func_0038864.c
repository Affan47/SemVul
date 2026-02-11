line (const GS &gs, int x1, int y1, int x2, int y2) {
    SDL_Rect s;
    sdl::copy_rect(s, gs.cliprect);
    SDL_SetClipRect (m_surface, &s);

    Uint8 r, g, b, a;
    SDL_GetRGBA (gs.pcolor, m_surface->format, &r, &g, &b, &a);

    if (has_flags(gs.flags, GS_ANTIALIAS))
        aalineRGBA (m_surface, x1, y1, x2, y2, r, g, b, a);
    else
        lineRGBA (m_surface, x1, y1, x2, y2, r, g, b, a);

    SDL_SetClipRect (m_surface, 0);
}

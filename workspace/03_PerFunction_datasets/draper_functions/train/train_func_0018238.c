drawOn(SDL_Surface *screen)
{
    Picture::drawOn(screen);
    if (m_activeColor == MASK_NO) {
        return;
    }

    SurfaceLock lock1(screen);
    SurfaceLock lock2(m_lowerLayer);
    SurfaceLock lock3(m_colorMask);


    for (int py = 0; py < m_colorMask->h; ++py) {
        int world_y = m_loc.getY() + py;
        for (int px = 0; px < m_colorMask->w; ++px) {
            Uint32 sample = PixelTool::getPixel(m_colorMask, px, py);

            if (sample == m_activeColor) {
                SDL_Color lower = PixelTool::getColor(m_lowerLayer, px, py);
                if (lower.unused == 255) {
                    PixelTool::putColor(screen,
                            m_loc.getX() + px, world_y, lower);
                }
            }
        }
    }
}

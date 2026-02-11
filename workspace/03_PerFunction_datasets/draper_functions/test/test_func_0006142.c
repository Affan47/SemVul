drawSurface(YSurface const & surface, int x, int y, int w, int h,
                           int const sx, int const sy,
#ifdef CONFIG_GRADIENTS
                           const int sw, const int sh) {
    if (surface.gradient != null)
        drawGradient(surface.gradient, x, y, w, h, sx, sy, sw, sh);
    else
#else
        const int , const int ) {
#endif
if (surface.pixmap != null)
    fillPixmap(surface.pixmap, x, y, w, h, sx, sy);
else if (surface.color) {
    setColor(surface.color);
    fillRect(x, y, w, h);
}
}

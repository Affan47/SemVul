updateNormalSize() {
    MSG(("updateNormalSize: %d %d %d %d", normalX, normalY, normalW, normalH));
    XSizeHints *sh = client()->sizeHints();

    bool cx = true;
    bool cy = true;
    bool cw = true;
    bool ch = true;

    if (isFullscreen() || isIconic())
        cy = ch = cx = cw = false;
    if (isMaximizedHoriz())
        cx = cw = false;
    if (isMaximizedVert())
        cy = ch = false;
    if (isRollup())
        ch = false;

    if (cx)
        normalX = posX + borderXN();
    if (cy)
        normalY = posY + borderYN();
    if (cw) {
        normalW = posW - 2 * borderXN();
        normalW = sh ? (normalW - sh->base_width) / sh->width_inc : normalW;
    }
    if (ch) {
        normalH = posH - (2 * borderYN() + titleYN());
        normalH = sh ? (normalH - sh->base_height) / sh->height_inc : normalH;
    }
    MSG(("updateNormalSize> %d %d %d %d", normalX, normalY, normalW, normalH));
}

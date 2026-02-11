updateMwmHints() {
    int bx = borderX();
    int by = borderY();
    int ty = titleY(), tt;

    getFrameHints();

    int gx, gy;
    client()->gravityOffsets(gx, gy);

#ifdef TITLEBAR_BOTTOM
    if (gy == -1)
#else
    if (gy == 1)
#endif
        tt = titleY() - ty;
    else
        tt = 0;

    if (!isRollup() && !isIconic())
        configureClient(x() + bx + bx - borderX(),
                        y() + by + by - borderY() + titleY(),
                        client()->width(), client()->height());
}

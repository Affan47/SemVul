ensureVisibility(int item) {
    if (item >= 0) {
        int oy = fOffsetY;
        int lh = getLineHeight();
        int fy = item * lh;

        if (fy + lh >= fOffsetY + (int)height())
            oy = fy + lh - height();
        if (fy <= fOffsetY)
            oy = fy;
        if (oy != fOffsetY) {
            fOffsetY = oy;
            repaint();
        }
    }
}

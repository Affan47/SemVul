cascadePlace(YFrameWindow **w, int count) {
    saveArrange(w, count);

    if (count == 0)
        return;

    int mx, my, Mx, My;
    manager->getWorkArea(0, &mx, &my, &Mx, &My);

    int lx = mx;
    int ly = my;
    for (int i = count; i > 0; i--) {
        YFrameWindow *f = w[i - 1];
        int x;
        int y;

        getCascadePlace(f, lx, ly, x, y, f->width(), f->height());
        f->setNormalPositionOuter(x, y);
    }
}

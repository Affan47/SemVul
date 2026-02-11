relayoutNow() {
    if (!fNeedRelayout)
        return ;

    fNeedRelayout = false;

    int nw = getRequiredWidth();
    if (nw != width()) {
        MSG(("tray: nw=%d x=%d w=%d", nw, x(), width()));
        setGeometry(YRect(x() + width() - nw, y(), nw, height()));
        fTaskBar->relayout();
    }

    int x, y, w, h;
    int tc = 0;

    for (TrayApp *a(fFirst); a != NULL; a = a->getNext())
        if (a->getShown()) tc++;

    w = h = height() - 4;
    x = width() - 2 - tc * w;
    y = 2;

    for (TrayApp *f(fFirst); f != NULL; f = f->getNext()) {
        if (f->getShown()) {
            f->setGeometry(YRect(x, y, w, h));
            f->show();
            x += w;
        } else
            f->hide();
    }
}

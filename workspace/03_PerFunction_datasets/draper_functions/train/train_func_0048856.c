Gtext (
    int wi, char *string, Gpoint_t go, char *fn, double fs,
    char *justs, Ggattr_t *ap
) {
    Gwidget_t *widget;
    char js[2];
    int n;

    if (wi < 0 || wi > Gwidgetn || !Gwidgets[wi].inuse) {
        Gerr (POS, G_ERRBADWIDGETID, wi);
        return -1;
    }
    widget = &Gwidgets[wi];
    if (string[0] == '\000')
        return 0;
    n = unpackstring (string);
    if (!justs[0] || !justs[1])
        js[0] = 'c', js[1] = 'c';
    else {
        js[0] = justs[0], js[1] = justs[1];
        if (js[0] != 'l' && js[0] != 'c' && js[0] != 'r')
            js[0] = 'c';
        if (js[1] != 'd' && js[1] != 'b' && js[1] != 'c' && js[1] != 'u')
            js[1] = 'c';
    }
    switch (widget->type) {
    case G_CANVASWIDGET:
        return GCtext (widget, &tlarray[0], n, go, fn, fs, &js[0], ap);
    case G_PCANVASWIDGET:
        return GPtext (widget, &tlarray[0], n, go, fn, fs, &js[0], ap);
    }
    Gerr (POS, G_ERRNOTACANVAS, wi);
    return -1;
}

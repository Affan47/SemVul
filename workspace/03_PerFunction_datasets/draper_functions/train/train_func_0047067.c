Gmenudisplay (int pwi, int wi) {
    Gwidget_t *parent, *widget;

    if (pwi < 0 || pwi > Gwidgetn || !Gwidgets[pwi].inuse) {
        Gerr (POS, G_ERRBADPARENTWIDGETID, wi);
        return -1;
    }
    if (wi < 0 || wi > Gwidgetn || !Gwidgets[wi].inuse) {
        Gerr (POS, G_ERRBADWIDGETID, wi);
        return -1;
    }
    parent = &Gwidgets[pwi];
    widget = &Gwidgets[wi];
    return GMmenudisplay (parent, widget);
}

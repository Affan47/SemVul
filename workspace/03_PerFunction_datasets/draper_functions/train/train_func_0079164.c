GPcreatebitmap (Gwidget_t *widget, Gbitmap_t *bitmap, Gsize_t s) {
    if (!widget) {
        Gerr (POS, G_ERRNOPARENTWIDGET);
        return -1;
    }
    if (!bitmap) {
        Gerr (POS, G_ERRNOBITMAP);
        return -1;
    }
    bitmap->u.bits = Marrayalloc ((long) ((int) s.x * (int) s.y * 3));
    bitmap->ctype = widget->type;
    bitmap->canvas = widget - &Gwidgets[0];
    bitmap->size = s;
    return 0;
}

getNormalGeometryInner(int *x, int *y, int *w, int *h) {
    XSizeHints *sh = client()->sizeHints();
    *x = normalX;
    *y = normalY;
    *w = sh ? normalW * sh->width_inc + sh->base_width : normalW;
    *h = sh ? normalH * sh->height_inc + sh->base_height : normalH;
}

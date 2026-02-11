sizePopup(int hspace) {
    int width, height;
    int maxName(0);
    int maxParam(0);
    int maxIcon(16);
    int l, t, r, b;
    int padx(1);
    int left(1);

    getOffsets(l, t, r, b);
    int dx, dy, dw, dh;
    desktop->getScreenGeometry(&dx, &dy, &dw, &dh, getXiScreen());

    width = l;
    height = t;

    for (int i = 0; i < itemCount(); i++) {
        const YMenuItem *mitem = getItem(i);

        int ih, top, bottom, pad;
        height+= (ih = mitem->queryHeight(top, bottom, pad));

        if (pad > padx) padx = pad;
        if (top > left) left = top;

        maxIcon = max(maxIcon, mitem->getIconWidth());
        maxName = max(maxName, mitem->getNameWidth());
        maxParam = max(maxParam, mitem->getParamWidth() +
                                (mitem->getSubmenu() ? 2 + ih : 0));
    }

    maxName = min(maxName, MenuMaximalWidth ? MenuMaximalWidth : dw * 2/3);

    hspace -= 4 + r + maxIcon + l + left + padx + 2 + maxParam + 6 + 2;
    hspace = max(hspace, dw / 3);


    if (maxName > hspace)
        maxName = hspace;

    namePos = l + left + padx + maxIcon + 2;
    paramPos = namePos + 2 + maxName + 6;
    width = paramPos + maxParam + 4 + r;
    height += b;

#ifdef CONFIG_GRADIENTS
    if (menubackPixbuf != null
        && !(fGradient != null &&
             fGradient->width() == width &&
             fGradient->height() == height)) {
        fGradient = menubackPixbuf->scale(width, height);
    }
#endif

    setSize(width, height);
}

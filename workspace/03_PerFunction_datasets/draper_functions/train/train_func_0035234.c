findItemPos(int itemNo, int &x, int &y, int &ih) {
    x = -1;
    y = -1;
    ih = 0;

    if (itemNo < 0 || itemNo > itemCount())
        return -1;

    int w, h;
    int top, bottom, pad;

    getArea(x, y, w, h);
    for (int i = 0; i < itemNo; i++) {
        y += getItem(i)->queryHeight(top, bottom, pad);
    }
    if (itemNo < itemCount())
        ih = getItem(itemNo)->queryHeight(top, bottom, pad);

    return 0;
}

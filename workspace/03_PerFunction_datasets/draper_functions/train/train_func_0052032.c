calcHeightUsing(const Length& h)
{
    int height = -1;
    if (!h.isAuto()) {
        if (h.isFixed())
            height = h.value();
        else if (h.isPercent())
            height = calcPercentageHeight(h);
        if (height != -1) {
            height = calcBoxHeight(height);
            return height;
        }
    }
    return height;
}

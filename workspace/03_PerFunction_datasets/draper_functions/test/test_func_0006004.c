getWidestItemWidthInList(const LBItemList &itemList, int itemDepth, float *widest) const
{
    size_t itemCount = itemList.size();
    for (size_t index = 0; index < itemCount; ++index)
    {
        Rect buttonLocation = itemList[index]->getButtonLocation();
        float thisWidth = itemList[index]->getPixelSize().d_width +
        buttonLocation.getWidth() +
        (d_horzScrollbar->getScrollPosition() / HORIZONTAL_STEP_SIZE_DIVISOR) +
        (itemDepth * 20);

        if (thisWidth > *widest)
            *widest = thisWidth;

        if (itemList[index]->getIsOpen() && (itemList[index]->getItemCount() > 0))
            getWidestItemWidthInList(itemList[index]->getItemList(), itemDepth + 1, widest);
    }
}

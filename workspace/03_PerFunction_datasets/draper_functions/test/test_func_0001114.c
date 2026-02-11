ensureItemIsVisibleHorz(const ItemEntry& item)
{
    const Rect render_area = getItemRenderArea();
    Scrollbar* const h = getHorzScrollbar();
    const float currPos = h->getScrollPosition();

    const float left =
        item.getXPosition().asAbsolute(this->getPixelSize().d_width) - currPos;
    const float right = left + item.getItemPixelSize().d_width;


    if ((left < render_area.d_left) || ((right - left) > render_area.getWidth()))
        h->setScrollPosition(currPos + left);

    else if (right >= render_area.d_right)
        h->setScrollPosition(currPos + right - render_area.getWidth());
}

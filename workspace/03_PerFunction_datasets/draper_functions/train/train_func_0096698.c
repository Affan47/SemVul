getUnclippedInnerRect() const
{
    const WidgetLookFeel& lf(getLookNFeel());

    if (lf.isNamedAreaDefined("inner_rect"))
        return lf.getNamedArea("inner_rect").getArea().
            getPixelRect(*d_window, d_window->getUnclippedOuterRect());
    else
        return d_window->getUnclippedOuterRect();
}

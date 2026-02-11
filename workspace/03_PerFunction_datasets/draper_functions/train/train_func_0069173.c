layout()
{
    KHTMLAssert( needsLayout());
    KHTMLAssert( minMaxKnown() );


    m_height = m_cachedImage && m_cachedImage->isErrorImage() ? intrinsicHeight() : 0;

    calcWidth();
    calcHeight();

    setNeedsLayout(false);
}

viewBoxToViewTransform(float viewWidth, float viewHeight) const
{
    FloatRect viewBoxRect;
    if (useCurrentView()) {
        if (currentView())
            viewBoxRect = currentView()->viewBox();
    } else
        viewBoxRect = viewBox();
    if (!viewBoxRect.width() || !viewBoxRect.height())
        return AffineTransform();

    AffineTransform ctm = preserveAspectRatio()->getCTM(viewBoxRect.x(),
            viewBoxRect.y(), viewBoxRect.width(), viewBoxRect.height(),
            0, 0, viewWidth, viewHeight);

    if (useCurrentView() && currentView())
        return currentView()->transform()->concatenate().matrix() * ctm;

    return ctm;
}

distance(const QSize& size, const QSize& desired,
                                 Plasma::Wallpaper::ResizeMethod method) const
{

    float delta = size.width() * size.height() -
                  desired.width() * desired.height();

    delta /= ((desired.width() * desired.height())+(size.width() * size.height()))/2;


    switch (method) {
    case Plasma::Wallpaper::ScaledResize: {


        float deltaRatio = 1.0;
        if (size.height() > 0 && desired.height() > 0) {
            deltaRatio = float(size.width()) / float(size.height()) -
                         float(desired.width()) / float(desired.height());
        }
        return fabs(deltaRatio) * 3.0 + (delta >= 0.0 ? delta : -delta + 5.0);
    }
    case Plasma::Wallpaper::ScaledAndCroppedResize:

        return delta >= 0.0 ? delta : -delta + 2.0;
    default:

        return fabs(delta);
    }
}

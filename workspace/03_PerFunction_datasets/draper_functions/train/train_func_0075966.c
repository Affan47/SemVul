blurBehindChanged(bool blur)
{
    if (blurActive != blur) {
        blurActive = blur;
        scheduleThemeChangeNotification(PixmapCache | SvgElementsCache);
    }
}

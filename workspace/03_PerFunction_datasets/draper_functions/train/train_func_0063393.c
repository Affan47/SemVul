wallpaperPath(const QSize &size) const
{
    QString fullPath;
    QString image = d->defaultWallpaperTheme;

    image.append("/contents/images/%1x%2").append(d->defaultWallpaperSuffix);
    QString defaultImage = image.arg(d->defaultWallpaperWidth).arg(d->defaultWallpaperHeight);

    if (size.isValid()) {


        image = image.arg(size.width()).arg(size.height());
    } else {
        image = defaultImage;
    }


    if (d->hasWallpapers) {

        fullPath = d->findInTheme(QLatin1Literal("wallpapers/") % image, d->themeName);

        if (fullPath.isEmpty()) {
            fullPath = d->findInTheme(QLatin1Literal("wallpapers/") % defaultImage, d->themeName);
        }
    }

    if (fullPath.isEmpty()) {


        fullPath = KStandardDirs::locate("wallpaper", image);
    }

    if (fullPath.isEmpty()) {


        fullPath = KStandardDirs::locate("wallpaper", defaultImage);

        if (fullPath.isEmpty()) {
            kDebug() << "exhausted every effort to find a wallpaper.";
        }
    }

    return fullPath;
}

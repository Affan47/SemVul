loadMimeTypeIcon( const QString& _iconName, KIconLoader::Group group, int size,
                                       int state, const QStringList& overlays, QString *path_store ) const
{
    QString iconName = _iconName;
    const int slashindex = iconName.indexOf(QLatin1Char('/'));
    if (slashindex != -1) {
        iconName[slashindex] = QLatin1Char('-');
    }

    if ( !d->extraDesktopIconsLoaded )
    {
        const QPixmap pixmap = loadIcon( iconName, group, size, state, overlays, path_store, true );
        if (!pixmap.isNull() ) {
            return pixmap;
        }
        const_cast<KIconLoader *>(this)->addExtraDesktopThemes();
    }
    const QPixmap pixmap = loadIcon(iconName, group, size, state, overlays, path_store, true);
    if (pixmap.isNull()) {

        return loadIcon("application-octet-stream", group, size, state, overlays, path_store, false);
    }
    return pixmap;
}

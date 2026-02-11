pixmap() const
{
    if ( !d->pixmapLabel ) {
        return QPixmap();
    }

    return *d->pixmapLabel->pixmap();
}

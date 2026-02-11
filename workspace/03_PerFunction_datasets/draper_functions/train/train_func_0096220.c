setImage(const QIcon &icon)
{
    d->image = icon.pixmap(IconSize(KIconLoader::Desktop));
}

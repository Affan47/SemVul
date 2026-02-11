sizeHint(Qt::SizeHint which, const QSizeF & constraint) const
{
    if (!d->dialogPtr || which != Qt::PreferredSize) {
        return Applet::sizeHint(which, constraint);
    }

    switch (formFactor()) {
        case Vertical:
        case Horizontal: {
            const int size = IconSize(KIconLoader::Panel);
            return QSizeF(size, size);
        }
        default:
            break;
    }

    const int size = IconSize(KIconLoader::Desktop);
    return QSizeF(size, size);
}

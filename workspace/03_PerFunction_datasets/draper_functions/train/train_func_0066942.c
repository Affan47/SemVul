key(int index) const
{
    QMetaEnumBuilderPrivate *d = d_func();
    if (d && index >= 0 && index < d->keys.size())
        return d->keys[index];
    else
        return QByteArray();
}

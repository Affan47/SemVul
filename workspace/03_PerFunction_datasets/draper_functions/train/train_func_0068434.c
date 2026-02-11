addKey(const QByteArray& name, int value)
{
    QMetaEnumBuilderPrivate *d = d_func();
    if (d) {
        int index = d->keys.size();
        d->keys += name;
        d->values += value;
        return index;
    } else {
        return -1;
    }
}

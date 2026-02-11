removeKey(int index)
{
    QMetaEnumBuilderPrivate *d = d_func();
    if (d && index >= 0 && index < d->keys.size()) {
        d->keys.removeAt(index);
        d->values.removeAt(index);
    }
}

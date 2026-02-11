setNotifySignal(const QMetaMethodBuilder& value)
{
    QMetaPropertyBuilderPrivate *d = d_func();
    if (d) {
        if (value._mobj) {
            d->notifySignal = value._index;
            d->setFlag(Notify, true);
        } else {
            d->notifySignal = -1;
            d->setFlag(Notify, false);
        }
    }
}

size() const
{
    if (d->size.isEmpty()) {
        d->size = d->naturalSize;
    }

    return d->size.toSize();
}

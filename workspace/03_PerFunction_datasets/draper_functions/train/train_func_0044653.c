map(QAbstractVideoBuffer::MapMode mode)
{
    if (d->buffer != 0 && d->data == 0) {
        Q_ASSERT(d->bytesPerLine == 0);
        Q_ASSERT(d->mappedBytes == 0);

        d->data = d->buffer->map(mode, &d->mappedBytes, &d->bytesPerLine);

        return d->data != 0;
    }

    return false;
}

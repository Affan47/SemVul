terminate()
{
    if ( d->mode == QIODevice::ReadOnly )
    {
        int result = inflateEnd(&d->zStream);
        if ( result != Z_OK ) {
            qDebug() << "inflateEnd returned " << result;

        }
    } else if ( d->mode == QIODevice::WriteOnly )
    {
        int result = deflateEnd(&d->zStream);
        if ( result != Z_OK ) {
            qDebug() << "deflateEnd returned " << result;

        }
    }
    d->isInitialized = false;
}

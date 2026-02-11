onReady()
{
    if(d->mDataSource)
        Q_EMIT data(d->mDataSource.data());
}

setDecodedData(const QByteArray &data)
{
    setData(data.toBase64());
    d->mDecodedDataCache = data;
    d->mSize = d->mDecodedDataCache.size();
}

saveFormDataToCache(const QString &key)
{
    if (d->wallet) {
        d->saveDataToCache(key);
        return;
    }
    d->openWallet();
}

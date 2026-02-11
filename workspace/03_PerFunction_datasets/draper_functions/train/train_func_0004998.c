hasEntry(const QString& key) {
#ifdef HAVE_KSECRETSSERVICE
    if (walletLauncher->m_useKSecretsService) {
        QExplicitlySharedDataPointer<KSecretsService::SecretItem> item = d->findItem( key );
        return item;
    }
    else {
#endif
        if (d->handle == -1) {
            return false;
        }

        QDBusReply<bool> r = walletLauncher->getInterface().hasEntry(d->handle, d->folder, key, appid());
        if (!r.isValid())
        {
            kDebug(285) << "Invalid DBus reply: " << r.error();
            return false;
        }
        else
            return r;
#ifdef HAVE_KSECRETSSERVICE
    }
#endif
}

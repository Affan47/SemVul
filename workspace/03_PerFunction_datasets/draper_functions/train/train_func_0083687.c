keyDoesNotExist(const QString& wallet, const QString& folder, const QString& key)
{
#ifdef HAVE_KSECRETSSERVICE
    if (walletLauncher->m_useKSecretsService) {
        kDebug(285) << "WARNING: changing semantics of keyDoesNotExist with KSS: will prompt for the password";
        Wallet *w = openWallet( wallet, 0, Synchronous );
        if ( w ) {
            return !w->hasEntry(key);
        }
        return false;
    }
    else {
#endif
        QDBusReply<bool> r = walletLauncher->getInterface().keyDoesNotExist(wallet, folder, key);
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

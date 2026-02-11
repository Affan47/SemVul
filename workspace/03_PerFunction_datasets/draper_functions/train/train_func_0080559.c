_k_openWalletDone(bool ok)
{
    Q_ASSERT (wallet);

    if (ok &&
        (wallet->hasFolder(KWallet::Wallet::FormDataFolder()) ||
         wallet->createFolder(KWallet::Wallet::FormDataFolder())) &&
         wallet->setFolder(KWallet::Wallet::FormDataFolder())) {


        if (!pendingFillRequests.isEmpty()) {
            KUrl::List urlList;
            QMutableHashIterator<KUrl, FormsData> requestIt (pendingFillRequests);
            while (requestIt.hasNext()) {
               requestIt.next();
               KWebWallet::WebFormList list = requestIt.value().forms;
               fillDataFromCache(list);
               q->fillWebForm(requestIt.key(), list);
            }

            pendingFillRequests.clear();
        }


        if (!pendingSaveRequests.isEmpty()) {
            QListIterator<QString> keysIt (pendingSaveRequests.keys());
            while (keysIt.hasNext())
                saveDataToCache(keysIt.next());
        }


        if (!pendingRemoveRequests.isEmpty()) {
            removeDataFromCache(pendingRemoveRequests);
            pendingRemoveRequests.clear();
        }
    } else {


        delete wallet.take();
    }
}

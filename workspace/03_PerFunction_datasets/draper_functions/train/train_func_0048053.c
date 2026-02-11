fillDataFromCache(KWebWallet::WebFormList &formList)
{
    if (!wallet) {
        kWarning(800) << "Unable to retrieve form data from wallet";
        return;
    }

    QString lastKey;
    QMap<QString, QString> cachedValues;
    QMutableListIterator <WebForm> formIt (formList);

    while (formIt.hasNext()) {
        KWebWallet::WebForm &form = formIt.next();
        const QString key (walletKey(form));
        if (key != lastKey && wallet->readMap(key, cachedValues) != 0) {
            kWarning(800) << "Unable to read form data for key:" << key;
            continue;
        }

        for (int i = 0, count = form.fields.count(); i < count; ++i) {
            form.fields[i].second = cachedValues.value(form.fields[i].first);
        }
        lastKey = key;
    }
}

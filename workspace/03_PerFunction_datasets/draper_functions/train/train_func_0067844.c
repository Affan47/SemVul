walletOpened(KWallet::Wallet *w) {
#ifndef KHTML_NO_WALLET
    assert(w);
    const QString key = calculateAutoFillKey(*this);
    if (!w->hasFolder(KWallet::Wallet::FormDataFolder())) {
        return;
    }
    w->setFolder(KWallet::Wallet::FormDataFolder());
    QMap<QString, QString> map;
    if (w->readMap(key, map))
        return;

    if(document()->view())
    {
        document()->view()->part()->addWalletFormKey(key);
    }
    for (QListIterator<HTMLGenericFormElementImpl*> it(formElements); it.hasNext();) {
        HTMLGenericFormElementImpl* const cur = it.next();
        if (cur->id() == ID_INPUT) {
            HTMLInputElementImpl* const current = static_cast<HTMLInputElementImpl*>(cur);
            if ((current->inputType() == HTMLInputElementImpl::PASSWORD ||
                    current->inputType() == HTMLInputElementImpl::TEXT) &&
                    !current->readOnly() &&
                    map.contains(current->name().string())) {
                document()->setFocusNode(current);
                current->setValue(map.value(current->name().string()));
            }
        }
    }
#endif
}

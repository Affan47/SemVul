slotDownloadDialogDestroyed()
{

    QHash<QString, QPointer<KDialog> >::iterator it = s_dialogs.begin();
    while (it != s_dialogs.end()) {
        if (it.value() == m_downloaddialog) {

            it = s_dialogs.erase(it);
        }

        if (it != s_dialogs.end()) {
            ++it;
        }
    }


}

open()
{
    QModelIndex index = tree->currentIndex();
    if (!index.parent().isValid())
        return;
    BrowserApplication::instance()->setEventMouseButtons(qApp->mouseButtons());
    BrowserApplication::instance()->setEventKeyboardModifiers(qApp->keyboardModifiers());
    emit openUrl(index.data(HistoryModel::UrlRole).toUrl(),
                 index.data(HistoryModel::TitleRole).toString());
}

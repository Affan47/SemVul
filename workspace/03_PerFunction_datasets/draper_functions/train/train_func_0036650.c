slotOk()
{
    QList<QTreeWidgetItem*> items = mListWidget->selectedItems();
    ProviderItem *item = static_cast<ProviderItem *>(items.first());
    if (!item) {
        KMessageBox::error(this, i18n("No provider selected."));
        return;
    }


    m_provider = item->provider();

    accept();
}

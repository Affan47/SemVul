multiSelectionChanged()
{
    if (locationEdit->hasFocus() && !locationEdit->currentText().isEmpty()) {
        return;
    }

    const KFileItemList list = ops->selectedItems();

    if (list.isEmpty()) {
        setLocationText(KUrl());
        return;
    }

    setLocationText(list.urlList());
}

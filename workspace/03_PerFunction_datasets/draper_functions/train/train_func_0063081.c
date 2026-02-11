deleteClicked()
{
    if (active || searchList->currentItem() == NULL) return;
    active = true;

    int index = searchList->invisibleRootItem()->indexOfChild(searchList->currentItem());
    mainWindow->namedSearches->getList().removeAt(index);
    delete searchList->invisibleRootItem()->takeChild(index);

    active = false;
    selectionChanged();
}

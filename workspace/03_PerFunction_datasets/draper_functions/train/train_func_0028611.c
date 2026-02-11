changeTitle(int id, const QString &text)
{
    QMenuItem* menuItem = findItem(id);
    Q_ASSERT(menuItem);
    if (!menuItem)
        return;
    menuItem->setText(text);
    menuItem->setIcon(QIcon());
    return;
}

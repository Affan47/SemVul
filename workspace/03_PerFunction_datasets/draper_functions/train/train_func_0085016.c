addTab(const QString &label, QGraphicsLayoutItem *content)
{
    return insertTab(d->pages.count(), QIcon(), label, content);
}

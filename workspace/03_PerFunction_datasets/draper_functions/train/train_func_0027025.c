mimeData(const QList<QListWidgetItem*> items) const
{
    if (items.isEmpty())
        return 0;
    QMimeData* mimedata = new QMimeData();

    QByteArray data;
    {
        QDataStream stream(&data, QIODevice::WriteOnly);

        ToolBarItem* item = static_cast<ToolBarItem *>(items.first());
        stream << *item;
    }

    mimedata->setData("application/x-kde-action-list", data);
    mimedata->setData("application/x-kde-source-treewidget", m_activeList ? "active" : "inactive");

    return mimedata;
}

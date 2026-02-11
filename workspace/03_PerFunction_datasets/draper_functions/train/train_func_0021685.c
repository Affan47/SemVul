save() const
{
    AppSettings->beginGroup("Favorites");

    QStringList list;
    m_model->toStringList(list);
    AppSettings->setValue("Files", list);

    QStringList attrList;
    m_model->toAttrStringList(attrList);
    AppSettings->setValue("Attributes", attrList);

    AppSettings->endGroup();

    QList<QVariant> indexList;
    m_model->toIndexList(indexList);
    AppSettings->setValue("Favorites/LastGameIndex", indexList);
}

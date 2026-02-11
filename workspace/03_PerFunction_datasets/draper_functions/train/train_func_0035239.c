operator>>(QDataStream& in, QContactSortOrder& sortOrder)
{
    sortOrder = QContactSortOrder();
    quint8 formatVersion;
    in >> formatVersion;
    if (formatVersion == 1) {
        QString definitionName;
        QString fieldName;
        quint32 blankPolicy;
        quint32 direction;
        quint32 caseSensitivity;
        in >> definitionName >> fieldName >> blankPolicy >> direction >> caseSensitivity;
        sortOrder.setDetailDefinitionName(definitionName, fieldName);
        sortOrder.setBlankPolicy(QContactSortOrder::BlankPolicy(blankPolicy));
        sortOrder.setDirection(Qt::SortOrder(direction));
        sortOrder.setCaseSensitivity(Qt::CaseSensitivity(caseSensitivity));
    } else {
        in.setStatus(QDataStream::ReadCorruptData);
    }
    return in;
}

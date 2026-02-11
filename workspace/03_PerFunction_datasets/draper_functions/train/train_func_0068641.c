data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (!index.parent().isValid() &&
            hasChildren(index) &&
            role==Qt::FontRole) {
        QFont bold;
        bold.setBold(true);
        return bold;
    }

    if (role==Qt::ToolTipRole) {
        Core::IToken *token = d->_tokensToItem.key(itemFromIndex(index));
        if (!token)
            return QStandardItemModel::data(index, role);
        return token->tooltip();
    }

    return QStandardItemModel::data(index, role);
}

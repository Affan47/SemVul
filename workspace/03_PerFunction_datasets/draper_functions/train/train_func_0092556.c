headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case 0: return tr("Rule");
        }
    }
    return QAbstractItemModel::headerData(section, orientation, role);
}

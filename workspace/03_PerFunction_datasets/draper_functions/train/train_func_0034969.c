removeRows(int row, int count, const QModelIndex & parent = QModelIndex())
    {
        beginRemoveRows(parent, row, row+count-1);
        for(int i=0; i < count; ++i) {
            m_List.removeAt(row);
        }
        endRemoveRows();
        return true;
    }

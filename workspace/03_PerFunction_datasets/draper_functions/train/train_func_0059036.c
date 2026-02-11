setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }

    bool ret = false;

    if (role == Qt::CheckStateRole) {
        static_cast<PluginEntry*>(index.internalPointer())->checked = value.toBool();
        ret = true;
    }

    if (ret) {
        emit dataChanged(index, index);
    }

    return ret;
}

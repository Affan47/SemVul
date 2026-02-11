data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::ToolTipRole) {
        Form::FormMain *form = d->formForIndex(index);
        if (!form)
            return QVariant();
        return formTooltip(form);
    }
    return QStandardItemModel::data(index, role);
}

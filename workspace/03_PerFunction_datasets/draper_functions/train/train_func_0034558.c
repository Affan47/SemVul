setItemText(QWidget *widget, const int row, const QString &item)
{
    QAbstractItemView *view = qobject_cast<QAbstractItemView*>(widget);
    if (view) {
        QAbstractItemModel *model = (QAbstractItemModel*)view->model();
        if (model) {
            QModelIndex idx = model->index(row, 0);
            model->setData(idx, item, Qt::DisplayRole);
            return true;
        }
    }
    QComboBox *combo = qobject_cast<QComboBox*>(widget);
    if (combo) {
        combo->setItemText(row, item);
        return true;
    }
    return false;
}

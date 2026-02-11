createEditor(QWidget* parent, const QStyleOptionViewItem& , const QModelIndex& ) const
{
    QComboBox* ret = new QComboBox(parent);
    ret->setEditable(false);
    return ret;
}

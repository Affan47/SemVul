sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const
{
    Q_ASSERT(_formTreeModel);
    const bool topLevel = !index.parent().isValid();
    if (topLevel) {


        QSize itemSize(10, 10);
        Form::FormMain *form = _formTreeModel->formForIndex(index);
        if (form) {
            if (form->extraData().contains("rootitemextraheight")) {
                itemSize = QSize(10, form->extraData().value("rootitemextraheight").toInt());
            } else {
                if (form->rootFormParent()->extraData().contains("rootitemextraheight")) {
                    itemSize = QSize(10, form->rootFormParent()->extraData().value("rootitemextraheight").toInt());
                }
            }
        }
        return QStyledItemDelegate::sizeHint(option, index) + itemSize;
    }
    return QStyledItemDelegate::sizeHint(option, index);
}

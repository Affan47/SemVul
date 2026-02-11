verticalLayout(const QStyleOptionViewItemV4 &option) const
{
    return (option.decorationPosition == QStyleOptionViewItem::Top ||
            option.decorationPosition == QStyleOptionViewItem::Bottom);
}

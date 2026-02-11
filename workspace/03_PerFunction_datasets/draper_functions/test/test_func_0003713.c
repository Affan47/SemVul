foregroundBrush(const QStyleOptionViewItemV4 &option, const QModelIndex &index) const
{
    QPalette::ColorGroup cg = QPalette::Active;
    if (!(option.state & QStyle::State_Enabled)) {
        cg = QPalette::Disabled;
    } else if (!(option.state & QStyle::State_Active)) {
        cg = QPalette::Inactive;
    }


    if (option.state & QStyle::State_Selected)
        return option.palette.brush(cg, QPalette::HighlightedText);


    const QVariant value = index.data(Qt::ForegroundRole);
    if (value.isValid())
        return brush(value, option);

    return option.palette.brush(cg, QPalette::Text);
}

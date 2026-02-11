drawHoverBackground(QPainter* painter)
{
    const bool isHovered = isHoverHintEnabled();
    if( isHovered )
    {
        QStyleOptionViewItemV4 option;
        option.initFrom(this);
        option.state = QStyle::State_Enabled | QStyle::State_Selected;
        option.viewItemPosition = QStyleOptionViewItemV4::OnlyOne;
        style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter, this );
    }
    else
    {
        QStyleOptionViewItemV4 option;
        option.initFrom(this);
        option.state = QStyle::State_Enabled | QStyle::State_MouseOver;
        option.viewItemPosition = QStyleOptionViewItemV4::OnlyOne;
        style()->drawPrimitive( QStyle::PE_PanelItemViewItem, &option, painter, this );
    }
}

drawFocusRect( QPainter *painter, QWidget *widget,
    const QRect &rect )
{
    QStyleOptionFocusRect opt;
    opt.init( widget );
    opt.rect = rect;
    opt.state |= QStyle::State_HasFocus;

    widget->style()->drawPrimitive( QStyle::PE_FrameFocusRect,
        &opt, painter, widget );
}

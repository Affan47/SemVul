paint(QPainter *painter, const QStyleOptionGraphicsItem * , QWidget* )
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(*mFrameBrush);
    painter->drawRoundedRect(mRect, 20, 20);

    painter->setBrush(*mFillBrush);
    painter->drawRoundedRect(mRectFill, 18, 18);

    if (mLabel != "")
    {
        painter->setRenderHint(QPainter::TextAntialiasing, true);
        painter->setPen(QPen(QColor("#303133")));
        painter->setFont(mFont);
        painter->drawText(mRectFill.adjusted(0, mYOffs, 0, mYOffs), Qt::AlignCenter, mLabel);
    }
}

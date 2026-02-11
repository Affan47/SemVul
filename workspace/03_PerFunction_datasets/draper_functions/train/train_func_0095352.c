setViewRect(const QRectF &rect)
{
    if (mWidget)
        mWidget->setPos(rect.x(), rect.y());

    if (mContactUI)
        mContactUI->setPos(rect.x(), rect.y());
}

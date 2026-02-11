onWidgetClosed(PlexyDesk::AbstractDesktopWidget *widget)
{
    qDebug() << Q_FUNC_INFO;
    PlexyDesk::AbstractDesktopView::onWidgetClosed(widget);
}

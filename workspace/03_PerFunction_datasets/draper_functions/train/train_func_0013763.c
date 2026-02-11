mousePressEvent(QMouseEvent* event)
{
    if (isAboveArrow(event->x()) && (event->button() == Qt::LeftButton)) {

        startSubDirsJob();
    }
    KUrlNavigatorButtonBase::mousePressEvent(event);
}

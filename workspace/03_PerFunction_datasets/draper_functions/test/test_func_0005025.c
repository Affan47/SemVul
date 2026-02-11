resizeEvent(QResizeEvent *ev)
{
    *thePixmap = QPixmap(ev->size());
}

paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.setClipRect(event->rect());
    drawCapacityBar(&p, contentsRect());
    p.end();
}

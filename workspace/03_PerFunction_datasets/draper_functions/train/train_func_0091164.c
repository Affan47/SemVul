mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::NoButton || isHidden()) {
        setDragState(None);
        return;
    }

    DragState h = spotHotSpot(e);


    if (h == Close) {
        setDragState(None);
        hide();

        return;
    } else if (h == Flip) {
        setDragState(None);
        flip();
    }


    oWidth = width();
    oHeight = height();
    oX = pos().x();
    oY = pos().y();
    mX = e->globalX();
    mY = e->globalY();

    setDragState(h);

    repaint();
}

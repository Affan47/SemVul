mousePressEvent(QMouseEvent *e)
{
    if (!resizable() || e->button() == Qt::NoButton || isHidden()) {
        setDragState(None);
        return;
    }

    DragState h = spotHotSpot(e);


    if (h == Close) {
        setDragState(None);
        return;
    } else if (h == Flip) {
        setDragState(None);
    }


    oWidth = width();
    oHeight = height();
    oWidthFactor = widthFactor();
    oHeightFactor = heightFactor();
    oX = pos().x();
    oY = pos().y();
    mX = mapFromGlobal(QCursor::pos()).x();
    mY = mapFromGlobal(QCursor::pos()).y();

    setDragState(h);

    repaint();
}

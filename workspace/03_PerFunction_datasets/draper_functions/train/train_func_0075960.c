open(int x, int y)
{
    m_menu->clear();
    foreach(QMenuItem* item, m_items) {
        m_menu->addAction (item);
    }

    QPoint screenPos;

    QGraphicsObject *parentItem;
    if (m_visualParent) {
        parentItem = qobject_cast<QGraphicsObject *>(m_visualParent.data());
    } else {
        parentItem = qobject_cast<QGraphicsObject *>(parent());
    }

    if (!parentItem || !parentItem->scene()) {
        m_menu->popup(QPoint(0, 0));
        m_status = DialogStatus::Open;
        emit statusChanged();
        return;
    }

    QList<QGraphicsView*> views = parentItem->scene()->views();

    if (views.size() < 1) {
        m_menu->popup(QPoint(0, 0));
        m_status = DialogStatus::Open;
        emit statusChanged();
        return;
    }

    QGraphicsView *view = 0;
    if (views.size() == 1) {
        view = views[0];
    } else {
        QGraphicsView *found = 0;
        QGraphicsView *possibleFind = 0;
        foreach (QGraphicsView *v, views) {
            if (v->sceneRect().intersects(parentItem->sceneBoundingRect()) ||
                v->sceneRect().contains(parentItem->scenePos())) {
                if (v->isActiveWindow()) {
                    found = v;
                } else {
                    possibleFind = v;
                }
            }
        }
        view = found ? found : possibleFind;
    }

    if (view) {
        screenPos = view->mapToGlobal(view->mapFromScene(parentItem->scenePos()+ QPoint(x, y)));
    } else {
        screenPos = QApplication::activeWindow()->mapToGlobal(QPoint(x, y));
    }

    m_menu->popup(screenPos);
    m_status = DialogStatus::Open;
    emit statusChanged();
}

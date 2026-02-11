open()
{
    m_menu->clear();

    foreach(QMenuItem* item, m_items) {
        m_menu->addAction (item);
    }
    m_menu->updateGeometry();

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

    if (!view) {
        m_menu->popup(QPoint(0, 0));
        m_status = DialogStatus::Open;
        emit statusChanged();
        return;
    }

    const QRect avail = QApplication::desktop()->availableGeometry(view);
    QPoint menuPos = view->mapToGlobal(view->mapFromScene(parentItem->scenePos()+QPoint(0, parentItem->boundingRect().height())));

    if (menuPos.y() + m_menu->sizeHint().height() > avail.bottom()) {
        menuPos = view->mapToGlobal(view->mapFromScene(parentItem->scenePos() - QPoint(0, m_menu->sizeHint().height())));
    }

    m_menu->popup(menuPos);
    m_status = DialogStatus::Open;
    emit statusChanged();
}

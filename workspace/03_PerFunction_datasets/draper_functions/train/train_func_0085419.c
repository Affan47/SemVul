handleKeyPressEvent(QKeyEvent *event)
    {
        if (!widget.data()) {
            event->ignore();
            return;
        }

        QPointF start = q->scrollPosition();
        QPointF end = start;

        qreal step = 100;

        switch (event->key()) {
        case Qt::Key_Left:
            if (canXFlick()) {
                end += QPointF(-step, 0);
            }
            break;
        case Qt::Key_Right:
            if (canXFlick()) {
                end += QPointF(step, 0);
            }
            break;
        case Qt::Key_Up:
            if (canYFlick()) {
                end += QPointF(0, -step);
            }
            break;
        case Qt::Key_Down:
            if (canYFlick()) {
                end += QPointF(0, step);
            }
            break;
        default:
            event->ignore();
            return;
        }

        fixupAnimation.groupX->stop();
        fixupAnimation.groupY->stop();
        fixupAnimation.snapX->stop();
        fixupAnimation.snapY->stop();
        directMoveAnimation->setStartValue(start);
        directMoveAnimation->setEndValue(end);
        directMoveAnimation->setDuration(200);
        directMoveAnimation->start();
    }

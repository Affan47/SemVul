barRect()
    {
        QRectF elementRect;

        if (labels.count() > 0) {
            elementRect = image->elementRect("background");
        } else {
            elementRect = QRectF(QPoint(0,0), meter->size());
        }

        if (image->hasElement("hint-bar-stretch") || !image->hasElement("bar-active-center")) {
            return elementRect;
        }

        QSize imageSize = image->size();
        image->resize();
        QSize tileSize = image->elementSize("bar-active-center");
        image->resize(imageSize);

        if (elementRect.width() > elementRect.height()) {
            qreal ratio = qMax(1, tileSize.height() / tileSize.width());
            int numTiles = qMax(qreal(1.0), qreal(elementRect.width())/(qreal(elementRect.height())/ratio));
            tileSize = QSize(elementRect.width()/numTiles, elementRect.height());

            QPoint center = elementRect.center().toPoint();
            elementRect.setWidth(tileSize.width()*numTiles);
            elementRect.moveCenter(center);
        } else {
            qreal ratio = qMax(1, tileSize.width() / tileSize.height());
            int numTiles = qMax(qreal(1.0), qreal(elementRect.height())/(qreal(elementRect.width())/ratio));
            tileSize = QSize(elementRect.width(), elementRect.height()/numTiles);

            QPoint center = elementRect.center().toPoint();
            elementRect.setHeight(tileSize.height()*numTiles);
            elementRect.moveCenter(center);
        }

        return elementRect;
    }

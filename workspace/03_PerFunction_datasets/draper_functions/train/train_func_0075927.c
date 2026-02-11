getImageData(float sx, float sy, float sw, float sh, int& exceptionCode)
{
    int w = qRound(sw);
    int h = qRound(sh);

    if (canvas()->isUnsafe()) {
        exceptionCode = DOMException::INVALID_ACCESS_ERR;
        return 0;
    }

    if (w <= 0 || h <= 0) {
        exceptionCode = DOMException::INDEX_SIZE_ERR;
        return 0;
    }

    if (!khtmlImLoad::ImageManager::isAcceptableSize(unsigned(w), unsigned(h))) {
        exceptionCode = DOMException::INDEX_SIZE_ERR;
        return 0;
    }

    int x = qRound(sx);
    int y = qRound(sy);

    CanvasImageDataImpl* id = new CanvasImageDataImpl(w, h);
    id->data.fill(Qt::transparent);


    QRect srcRect = QRect(x, y, w, h);
    QRect clpRect = srcRect & QRect(0, 0, canvasElement->width(), canvasElement->height());
    if (!clpRect.isEmpty()) {
        QPainter p(&id->data);
        p.setCompositionMode(QPainter::CompositionMode_Source);


        syncBackBuffer();


        QImage* backBuffer = canvasImage->qimage();
        p.drawImage(clpRect.topLeft() - srcRect.topLeft(), *backBuffer, clpRect);
        p.end();
    }

    return id;
}

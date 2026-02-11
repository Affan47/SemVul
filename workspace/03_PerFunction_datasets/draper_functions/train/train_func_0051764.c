putImageData(CanvasImageDataImpl* id, float dx, float dy, int& exceptionCode)
{
    if (!id) {
        exceptionCode = DOMException::TYPE_MISMATCH_ERR;
        return;
    }


    syncBackBuffer();


    needRendererUpdate();
    QPainter p(canvasImage->qimage());
    int x = qRound(dx);
    int y = qRound(dy);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.drawImage(x, y, id->data);
}

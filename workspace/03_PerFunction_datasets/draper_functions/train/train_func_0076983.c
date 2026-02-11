shadowBlur(QImage &image, float radius, const QColor &color)
{
    if (radius < 0)
        return;

    if (radius > 0)
        stackBlur(image, radius);


    QPainter p(&image);
    p.setCompositionMode(QPainter::CompositionMode_SourceIn);
    p.fillRect(image.rect(), color);
}

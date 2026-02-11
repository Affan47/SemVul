checkImageCache()
{
    if (!m_imageCacheDirty)
        return;

    QPixmap img(qFloor(width()), qFloor(height()));
    img.fill(Qt::transparent);
    QPainter painter(&img);
    painter.scale(m_textScale, m_textScale);
    m_doc->drawContents(&painter);

    m_imageCache = img;
    m_imageCacheDirty = false;

    update();
}

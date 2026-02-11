resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    m_scaledImage = QImage();
    repaint();
}

previous()
{
    if (m_CurrentIndex >= 1) {
        --m_CurrentIndex;
        imageLabel->setPixmap(m_pixmaps.at(m_CurrentIndex));
        normalSize();
        fitToWindow();
    }
}

calcMinWidth() const
{
    return qMax(QFontMetrics(m_titleFont).width(m_titleText) + 12, QWidget::sizeHint().width());
}

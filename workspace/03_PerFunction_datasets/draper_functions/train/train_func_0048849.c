setData(const QPixmap &icon, const QString &text)
{
    m_icon->setPixmap(icon);
    m_name->setText("<font size=\"5\">" + text + "</font>");
}

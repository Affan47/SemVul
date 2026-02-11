setText(const QString& text)
{
    QString adjustedText = text;
    if (adjustedText.isEmpty()) {
        adjustedText = m_url.protocol();
    }

    adjustedText.remove(QLatin1Char('\n'));

    KUrlNavigatorButtonBase::setText(adjustedText);
    updateMinimumWidth();


    m_pendingTextChange = false;
}

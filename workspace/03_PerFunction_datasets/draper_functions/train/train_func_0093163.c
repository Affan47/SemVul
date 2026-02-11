frameTextReadonly() const
{
    if (!m_frameTextItem)
        return false;
    return m_frameTextItem->textInteractionFlags() == Qt::NoTextInteraction;
}

foregroundColor() const
{
    const bool isHighlighted = isDisplayHintEnabled(EnteredHint) ||
                               isDisplayHintEnabled(DraggedHint) ||
                               isDisplayHintEnabled(PopupActiveHint);

    QColor foregroundColor = palette().color(foregroundRole());

    int alpha = m_active ? 255 : 128;
    if (!m_active && !isHighlighted) {
        alpha -= alpha / 4;
    }
    foregroundColor.setAlpha(alpha);

    return foregroundColor;
}

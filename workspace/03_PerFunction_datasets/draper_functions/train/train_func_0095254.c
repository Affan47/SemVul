mapToButton(const QPointF &point) const
{
    int iconMargin = m_iconSize / 2;

    QPointF basePoint = m_rect.topLeft() + QPointF(HANDLE_MARGIN, iconMargin);
    QPointF step = QPointF(0, m_iconSize + iconMargin);
    QPointF separator = step + QPointF(0, iconMargin);


    QRectF activeArea = QRectF(basePoint, QSizeF(m_iconSize, m_iconSize));

    if (m_applet && m_applet->aspectRatioMode() != FixedSize) {
        if (activeArea.contains(point)) {
            return ResizeButton;
        }
        activeArea.translate(step);
    }

    if (activeArea.contains(point)) {
        return RotateButton;
    }

    if (m_applet && m_applet->hasConfigurationInterface()) {
        activeArea.translate(step);
        if (activeArea.contains(point)) {
            return ConfigureButton;
        }
    }

    if (m_applet && m_applet->hasValidAssociatedApplication()) {
        activeArea.translate(step);
        if (activeArea.contains(point)) {
            return MaximizeButton;
        }
    }

    activeArea.moveTop(m_rect.bottom() - activeArea.height() - iconMargin);
    if (activeArea.contains(point)) {
        return RemoveButton;
    }

    return MoveButton;

}

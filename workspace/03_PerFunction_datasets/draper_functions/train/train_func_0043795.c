slotVisibilityChanged(bool visible)
{
    if (visible && document() && !m_filled) {
        fillInfo();
        m_filled = true;
    }
}

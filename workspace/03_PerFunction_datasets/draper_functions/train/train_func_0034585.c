sizeHint() const
{
    QSize sh = tabSizeHint();
    return Side!=m_pos
            ? QSize(sh.width() * m_tabs.count(), sh.height())
            : QSize(sh.width(), sh.height() * m_tabs.count());
}

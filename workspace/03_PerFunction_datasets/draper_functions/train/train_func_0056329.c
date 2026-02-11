textMargin(WidgetPosition position) const
{
    int spacing = m_rightLayout->spacing();
    int w = 0;
    if (position == LeftSide)
        w = m_leftWidget->sizeHint().width();
    else
        w = m_rightWidget->sizeHint().width();
    if (w == 0)
        return 0;
    return w + spacing * 2;
}

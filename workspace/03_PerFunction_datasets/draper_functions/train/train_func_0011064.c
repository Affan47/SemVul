layoutChildren()
{

    foreach (CornerItem * corner, m_cornerItems)
        corner->relayout(m_contentRect);


    if (m_frame) {
        m_frame->layoutButtons(m_controlItems, m_frameRect.toRect());
        if (m_frameTextItem)
            m_frame->layoutText(m_frameTextItem, m_frameRect.toRect());
    } else {

        const int spacing = 4;
        int left = m_frameRect.left();
        int top = m_frameRect.top();
        int right = m_frameRect.right();
        int bottom = m_frameRect.bottom();
        int offset = right;
        foreach (ButtonItem * button, m_controlItems) {
            switch (button->buttonType()) {
                case ButtonItem::FlipH:
                    button->setPos(right - button->width() / 2, (top + bottom) / 2);
                    break;

                case ButtonItem::FlipV:
                    button->setPos((left + right) / 2, top + button->height() / 2);
                    break;

                default:
                    button->setPos(offset - button->width() / 2, bottom - button->height() / 2);
                    offset -= button->width() + spacing;
                    break;
            }
        }

        if (m_frameTextItem)
            m_frameTextItem->hide();
    }
}

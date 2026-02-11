deleteLastLineBox(RenderArena* arena)
{
    if (m_lastLineBox) {
        if (!arena)
            arena = renderArena();
        InlineRunBox *curr=m_lastLineBox, *prev = m_lastLineBox;
        if (m_firstLineBox == m_lastLineBox)
            m_firstLineBox = m_lastLineBox = 0;
        else {
            prev = curr->prevLineBox();
            while (!prev->isInlineFlowBox()) {
                prev = prev->prevLineBox();
                prev->detach(arena);
            }
            m_lastLineBox = static_cast<InlineFlowBox*>(prev);
            prev->setNextLineBox(0);
        }
        if (curr->parent()) {
            curr->parent()->removeFromLine(curr);
        }
        curr->detach(arena);
    }
}

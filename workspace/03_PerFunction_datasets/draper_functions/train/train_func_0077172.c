attachLineBox(InlineFlowBox* box)
{
    if (m_lastLineBox) {
        m_lastLineBox->setNextLineBox(box);
        box->setPreviousLineBox(m_lastLineBox);
    } else
        m_firstLineBox = box;
    InlineFlowBox* last = box;
    for (InlineFlowBox* curr = box; curr; curr = curr->nextFlowBox()) {
        curr->setExtracted(false);
        last = curr;
    }
    m_lastLineBox = last;
}

extractLineBox(InlineFlowBox* box)
{
    m_lastLineBox = box->prevFlowBox();
    if (box == m_firstLineBox)
        m_firstLineBox = 0;
    if (box->prevLineBox())
        box->prevLineBox()->setNextLineBox(0);
    box->setPreviousLineBox(0);
    for (InlineRunBox* curr = box; curr; curr = curr->nextLineBox())
        curr->setExtracted();
}

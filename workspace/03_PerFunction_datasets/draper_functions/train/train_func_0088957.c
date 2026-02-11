createInlineBox(bool makePlaceHolderBox, bool isRootLineBox)
{
    if ( !isRootLineBox &&
         (isReplaced() || makePlaceHolderBox) )
         return RenderBox::createInlineBox(false, false);

    InlineFlowBox* flowBox = 0;
    if (isInlineFlow())
        flowBox = new (renderArena()) InlineFlowBox(this);
    else
        flowBox = new (renderArena()) RootInlineBox(this);

    if (!m_firstLineBox) {
        m_firstLineBox = m_lastLineBox = flowBox;
    } else {
        m_lastLineBox->setNextLineBox(flowBox);
        flowBox->setPreviousLineBox(m_lastLineBox);
        m_lastLineBox = flowBox;
    }

    return flowBox;
}

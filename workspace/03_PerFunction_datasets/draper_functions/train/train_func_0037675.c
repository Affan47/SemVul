detach(RenderArena* arena, bool noRemove)
{
    if (m_lineBreakContext)
        m_lineBreakContext->deref();
    m_lineBreakContext = 0;
    detachEllipsisBox(arena);
    InlineFlowBox::detach(arena, noRemove);

}

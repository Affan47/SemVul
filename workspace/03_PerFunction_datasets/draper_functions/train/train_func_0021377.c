setHasVisibleContent(bool b)
{
    if (m_hasVisibleContent == b && !m_visibleContentStatusDirty)
        return;
    m_visibleContentStatusDirty = false;
    m_hasVisibleContent = b;
    if (m_hasVisibleContent) {


        if (!isOverflowOnly())
            if (RenderLayer* sc = stackingContext())
                sc->dirtyZOrderLists();
    }
    if (parent())
        parent()->childVisibilityChanged(m_hasVisibleContent);
}

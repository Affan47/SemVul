attach()
{
    assert(!attached());
    assert(!m_render);
    assert(parentNode());

    RenderStyle* _style = document()->styleSelector()->styleForElement(this);
    _style->ref();
    if (parentNode()->renderer() && parentNode()->renderer()->childAllowed() &&
        _style->display() != NONE)
    {
        m_render = new (document()->renderArena()) RenderCanvasImage(this);
        m_render->setStyle(_style);
        parentNode()->renderer()->addChild(m_render, nextRenderer());
    }
    _style->deref();

    NodeBaseImpl::attach();
    if (m_render)
        m_render->updateFromElement();
}

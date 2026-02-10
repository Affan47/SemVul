attach()
{
    assert(!attached());
    assert(!m_render);
    assert(parentNode());

    RenderStyle* const _style = document()->styleSelector()->styleForElement(this);
    _style->ref();
    if (parentNode()->renderer() && _style->display() != NONE) {
        m_render = new (document()->renderArena()) RenderTextArea(this);
        m_render->setStyle(_style);
    }

    HTMLGenericFormElementImpl::attach();
    _style->deref();
}

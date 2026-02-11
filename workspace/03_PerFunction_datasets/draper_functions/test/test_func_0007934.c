detach()
{
    RenderObject* render = m_render;


    m_render = 0;

    delete m_tokenizer;
    m_tokenizer = 0;


    m_imageLoadEventDispatchSoonList.clear();
    m_imageLoadEventDispatchingList.clear();
    NodeBaseImpl::detach();

    if ( render )
        render->detach();

    m_view = 0;

    m_renderArena.reset();
}

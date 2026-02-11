width_client()
{
#ifdef _DEBUG
    if( m_drawarea ) std::cout << "ArticleViewBase::width_client : " << m_drawarea->width_client() << std::endl;
#endif

    if( m_drawarea ) return m_drawarea->width_client();

    return SKELETON::View::width_client();
}

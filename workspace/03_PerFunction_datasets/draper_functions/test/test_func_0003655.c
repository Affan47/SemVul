BoardViewNext( const std::string& url, const std::string& url_pre_article )
    : BoardViewBase( url, false ),
      m_url_pre_article( url_pre_article )
{
    set_writeable( false );

#ifdef _DEBUG
    std::cout << "BoardViewNext::BoardViewNext : url = " << get_url() << std::endl;
#endif
}

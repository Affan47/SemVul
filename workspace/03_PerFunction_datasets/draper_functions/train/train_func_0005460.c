add_abone_name( const std::string& name )
{
    if( empty() ) return;
    if( name.empty() ) return;

#ifdef _DEBUG
    std::cout << "ArticleBase::add_abone_name : " << name << std::endl;
#endif

    m_list_abone_name.push_back( name );

    update_abone();

    m_save_info = true;
}

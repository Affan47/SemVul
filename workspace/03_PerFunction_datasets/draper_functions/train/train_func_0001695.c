create_nodetree()
{
#ifdef _DEBUG
    std::cout << "ArticleJBBS::create_nodetree " << get_url() << std::endl;
#endif

    return new NodeTreeJBBS( get_url(), get_date_modified() );
}

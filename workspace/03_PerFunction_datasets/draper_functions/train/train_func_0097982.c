get_history( const std::string& url, CORE::DATA_INFO_LIST& info_list )
{
    info_list.clear();

    BBSListViewBase* view = dynamic_cast< BBSListViewBase* >( get_view( url ) );
    if( view ) return view->get_history( info_list );
}

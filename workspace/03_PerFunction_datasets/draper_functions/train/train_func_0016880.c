set_list_info_selected( const CORE::DATA_INFO_LIST& list_info_selected )
{
#ifdef _DEBUG
    std::cout << "UNDO_BUFFER::set_list_info_selected\n";
#endif

    UNDO_ITEM item;
    item.list_info_selected = list_info_selected;
    set_item( item );
}

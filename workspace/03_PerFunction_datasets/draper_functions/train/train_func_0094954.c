HistoryBoardView( const std::string& url, const std::string& arg1, const std::string& arg2 )
    : HistoryViewBase( url, CACHE::path_xml_history_board(), arg1, arg2 )
{
    set_label( ITEM_NAME_HIST_BOARDVIEW );
}

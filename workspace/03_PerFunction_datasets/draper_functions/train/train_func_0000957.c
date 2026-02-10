drawMsgWin( WINDOW* win, std::vector<std::string> words )
{
    wclear( win );
    box( win, 0, 0 );

    int i = 1;
    std::vector<std::string>::const_iterator j = words.begin();
    while( j != words.end() ) {
	mvwprintw( win, i, 1, j->c_str() );
	i++;
	j++;
    }

    wrefresh( win );
}

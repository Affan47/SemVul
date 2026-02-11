open_window()
{
    SKELETON::JDWindow* win = get_jdwin();

    if( ! SESSION::get_embedded_mes() && ! win && ! empty() ){

#ifdef _DEBUG
    std::cout << "MessageAdmin::open_window\n";
#endif

        win = new MESSAGE::MessageWin();
        set_jdwin( win );
        win->pack_remove_end( false, *get_widget() );
        win->show_all();
    }
    else if( win && win->is_hide() ){
        win->show();
        win->focus_in();
    }
}

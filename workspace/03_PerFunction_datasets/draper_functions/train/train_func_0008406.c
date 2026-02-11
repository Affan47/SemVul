load_text()
{
    if( get_path().empty() ) return;

    init();
    set_code( HTTP_INIT );
    receive_finish();
}

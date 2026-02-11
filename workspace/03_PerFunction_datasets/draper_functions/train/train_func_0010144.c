client_render_topic(
    int x, int y, SDL_Surface *buffer )
{
    if ( y >= client_topic_count ) return 0;
    chat_font_normal->align = STK_FONT_ALIGN_LEFT;
    stk_font_write( chat_font_normal,
        buffer, 2,0, STK_OPAQUE,
        client_topics[y] );
    return 1;
}

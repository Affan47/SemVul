edit_show( Edit *edit, const char *newtext )
{
    int i, w = 0;
    if ( newtext )
        strcpy_lt( edit->text, newtext, edit->limit );

    edit->last_sym = -1;

    event_clear_sdl_queue();

    for ( i = 0; i < edit->cursor_pos; i++ )
        w += char_width( edit->label->def_font, edit->text[i] );
    edit->cursor_x = ( ( edit->label->frame->img->img->w - text_width( edit->label->def_font, edit->text ) ) >> 1 ) + w;

    edit->blink = 1;
    edit->blink_time = 0;

    label_write( edit->label, 0, edit->text );
}

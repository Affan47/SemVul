text_mode_copy_to_clipboard(TextRender *obj, offset_type start_offset, offset_type end_offset)
{
    g_return_if_fail (obj!=NULL);
    g_return_if_fail (start_offset!=end_offset);
    g_return_if_fail (obj->priv->dp!=NULL);
    g_return_if_fail (obj->priv->im!=NULL);

    GtkClipboard *clip = gtk_clipboard_get_for_display (gdk_display_get_default (), GDK_SELECTION_CLIPBOARD);
    g_return_if_fail (clip!=NULL);

    text_render_utf8_clear_buf(obj);
    offset_type current = start_offset;
    while (current < end_offset &&  obj->priv->utf8buf_length<MAX_CLIPBOARD_COPY_LENGTH)
    {
        char_type value = gv_input_mode_get_utf8_char(obj->priv->im, current);
        if (value==INVALID_CHAR)
            break;

        current = gv_input_get_next_char_offset(obj->priv->im, current);
        text_render_utf8_print_char(obj, value);
    }

    gtk_clipboard_set_text(clip, (const gchar *) obj->priv->utf8buf, obj->priv->utf8buf_length);
}

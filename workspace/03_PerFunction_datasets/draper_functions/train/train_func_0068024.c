ibus_unikey_engine_update_preedit_string(IBusEngine *engine, const gchar *string, gboolean visible)
{
    IBusText *text;

    unikey = (IBusUnikeyEngine*)engine;

    text = ibus_text_new_from_static_string(string);


    ibus_text_append_attribute(text, IBUS_ATTR_TYPE_UNDERLINE, IBUS_ATTR_UNDERLINE_SINGLE, 0, -1);


    ibus_engine_update_preedit_text(engine, text, ibus_text_get_length(text), visible);


    if (unikey->mouse_capture)
    {

        pthread_mutex_unlock(&mutex_mcap);
    }
}

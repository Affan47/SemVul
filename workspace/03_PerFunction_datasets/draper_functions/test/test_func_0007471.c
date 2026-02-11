gcut_source_string_dispatch (GSource *source, GSourceFunc callback,
                             gpointer user_data)

{
    GCutStringSource *string_source = (GCutStringSource *)source;
    GIOFunc func = (GIOFunc)callback;

    if (func)
        return func(string_source->channel,
                    string_source->available_condition,
                    user_data);
    else
        return FALSE;
}

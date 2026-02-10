source_is_available (GSource *source)
{
    GCutStringSource *string_source = (GCutStringSource *)source;
    GIOChannel *channel;
    GCutStringIOChannel *string_channel;
    GIOCondition available_buffer_condition;
    GIOCondition all_input_condition, all_error_condition;

    channel = string_source->channel;
    string_channel = (GCutStringIOChannel *)(channel);
    string_source->available_condition = 0;
    available_buffer_condition =
        g_io_channel_get_buffer_condition(channel) &
        string_source->condition;

    all_input_condition = (G_IO_IN | G_IO_PRI);
    if (string_source->condition & all_input_condition &&
        channel->is_readable) {
        string_source->available_condition |= available_buffer_condition;
        if (string_channel->string &&
            ((string_channel->string->len > string_channel->read_offset) ||
             (!string_channel->pipe_mode &&
              string_channel->string->len == string_channel->read_offset &&
              !string_channel->reach_eof)))
            string_source->available_condition |=
                (all_input_condition & string_source->condition);
    }

    if (string_source->condition & G_IO_OUT && channel->is_writeable)
        string_source->available_condition |= G_IO_OUT;

    all_error_condition = (G_IO_ERR | G_IO_HUP | G_IO_NVAL);
    if (string_source->condition & all_error_condition) {
        string_source->available_condition |= available_buffer_condition;
        if (string_channel->string == NULL)
            string_source->available_condition |=
                (all_error_condition & string_source->condition);
    }

    return string_source->available_condition > 0;
}

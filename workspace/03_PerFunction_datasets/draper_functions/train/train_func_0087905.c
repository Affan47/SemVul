commands_prepare_info_source(struct annotate_two *a2, struct commands *c,
        enum COMMAND_STATE state)
{
    data_set_state(a2, INTERNAL_COMMAND);
    ibuf_clear(c->info_source_string);
    ibuf_clear(c->info_source_relative_path);
    ibuf_clear(c->info_source_absolute_path);

    if (state == INFO_SOURCE_FILENAME_PAIR)
        commands_set_state(c, INFO_SOURCE_FILENAME_PAIR, NULL);
    else if (state == INFO_SOURCE_RELATIVE)
        commands_set_state(c, INFO_SOURCE_RELATIVE, NULL);

    c->info_source_ready = 0;
}

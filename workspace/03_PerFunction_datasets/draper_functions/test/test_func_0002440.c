commands_initialize(void)
{
    struct commands *c =
            (struct commands *) cgdb_malloc(sizeof (struct commands));
    const char *regex = "[io]n (.*) at (.*):([0-9]+)";

    c->absolute_path = ibuf_init();
    c->line_number = ibuf_init();

    c->cur_command_state = VOID_COMMAND;
    c->cur_field_num = 0;

    c->breakpoint_list = tgdb_list_init();
    c->breakpoint_string = ibuf_init();
    c->breakpoint_table = 0;
    c->breakpoint_enabled = 0;
    c->breakpoint_started = 0;
    if (regcomp(&c->regex_bp, regex, REG_EXTENDED) != 0)
        return NULL;

    c->info_source_string = ibuf_init();
    c->info_source_relative_path = ibuf_init();
    c->info_source_absolute_path = ibuf_init();
    c->info_source_ready = 0;
    c->last_info_source_requested = ibuf_init();

    c->sources_ready = 0;
    c->info_sources_string = ibuf_init();
    c->inferior_source_files = tgdb_list_init();

    c->tab_completion_ready = 0;
    c->tab_completion_string = ibuf_init();
    c->tab_completions = tgdb_list_init();

    c->source_prefix = "Located in ";
    c->source_prefix_length = 11;

    c->source_relative_prefix = "Current source file is ";
    c->source_relative_prefix_length = 23;

    return c;
}

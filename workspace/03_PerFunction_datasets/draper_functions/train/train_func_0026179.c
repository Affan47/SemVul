commands_set_state(struct commands *c,
        enum COMMAND_STATE state, struct tgdb_list *list)
{
    c->cur_command_state = state;

    switch (c->cur_command_state) {
        case RECORD:
            if (ibuf_length(c->breakpoint_string) > 0) {
                if (parse_breakpoint(c) == -1)
                    logger_write_pos(logger, __FILE__, __LINE__,
                            "parse_breakpoint error");

                ibuf_clear(c->breakpoint_string);
                c->breakpoint_enabled = 0;
            }
            break;
        case BREAKPOINT_TABLE_END:
            if (ibuf_length(c->breakpoint_string) > 0)
                if (parse_breakpoint(c) == -1)
                    logger_write_pos(logger, __FILE__, __LINE__,
                            "parse_breakpoint error");
            {
                struct tgdb_response *response = (struct tgdb_response *)
                        cgdb_malloc(sizeof (struct tgdb_response));

                response->header = TGDB_UPDATE_BREAKPOINTS;
                response->choice.update_breakpoints.breakpoint_list =
                        c->breakpoint_list;


                tgdb_types_append_command(list, response);
            }

            ibuf_clear(c->breakpoint_string);
            c->breakpoint_enabled = 0;

            c->breakpoint_started = 0;
            break;
        case BREAKPOINT_HEADERS:
            c->breakpoint_table = 0;
            break;
        case BREAKPOINT_TABLE_BEGIN:


            c->breakpoint_table = 1;
            c->breakpoint_started = 1;
            break;
        case INFO_SOURCE_FILENAME_PAIR:
            break;
        case INFO_SOURCE_RELATIVE:
            break;
        case INFO_SOURCES:
            break;
        default:
            break;
    }
}

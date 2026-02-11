register_one_ram_block(xlnk_script *s, xlnk_script_command *c, void *arg)
{
    int start;
    int end;
    const char *start_str;
    const char *end_str;
    require_arg(s, c, "start", start_str);
    require_arg(s, c, "end", end_str);
    start = str_to_int(start_str);
    end = str_to_int(end_str);
    require_arg_in_range(s, c, "start", start, 0x0000, 0xFFFF);
    require_arg_in_range(s, c, "end", end, 0x0000, 0xFFFF);
    if (end <= start) {
        scripterr(s, c, "`end' is smaller than `start'");
    }
    add_ram_block(start, end);
}

il_kill_to_end_of_line()
{
    size_t old_mark = il->mark;

    il_set_mark();
    il_end_of_line();
    il_region_command(IL_STORE | IL_KILL);
    il->mark = min(old_mark, il->length);

    il->last_operation = IL_KILL_TO_END_OF_LINE;
}

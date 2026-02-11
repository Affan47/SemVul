matchCommand(const char * pattern, const char * cmd, size_t len) {
    int result = FALSE;

    const char * pattern_ptr = pattern;
    int pattern_len = strlen(pattern);
    const char * pattern_end = pattern + pattern_len;

    const char * cmd_ptr = cmd;
    size_t cmd_len = SCPI_strnlen(cmd, len);
    const char * cmd_end = cmd + cmd_len;


    if (iscolon(cmd_ptr[0])) {
        cmd_len --;
        cmd_ptr ++;
    }

    while (1) {
        int pattern_sep_pos = patternSeparatorPos(pattern_ptr, pattern_end - pattern_ptr);
        int cmd_sep_pos = cmdSeparatorPos(cmd_ptr, cmd_end - cmd_ptr);

        if (matchPattern(pattern_ptr, pattern_sep_pos, cmd_ptr, cmd_sep_pos)) {
            pattern_ptr = pattern_ptr + pattern_sep_pos;
            cmd_ptr = cmd_ptr + cmd_sep_pos;
            result = TRUE;


            if ((pattern_ptr == pattern_end) && (cmd_ptr >= cmd_end)) {
                break;
            }


            if ((pattern_ptr == pattern_end) && (cmd_ptr < cmd_end)) {
                result = FALSE;
                break;
            }


            if (cmd_ptr >= cmd_end) {
                result = FALSE;
                break;
            }


            if ((pattern_ptr[0] == cmd_ptr[0]) && ((pattern_ptr[0] == ':') || (pattern_ptr[0] == '?'))) {
                pattern_ptr = pattern_ptr + 1;
                cmd_ptr = cmd_ptr + 1;
            } else {
                result = FALSE;
                break;
            }
        } else {
            result = FALSE;
            break;
        }
    }

    return result;
}

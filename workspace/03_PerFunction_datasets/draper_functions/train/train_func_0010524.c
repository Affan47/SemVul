suppress_space(void) {
    int i;
    for (i = line_start(rl_point); i < rl_point; i++)
        if (rl_line_buffer[i] != ' ') return 0;
    if (spaces_suppressed < strip_initial_spaces) return 1;
    return 0;
}

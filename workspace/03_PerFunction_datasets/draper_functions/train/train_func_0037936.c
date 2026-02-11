backspace_callback(int count, int key) {
    reset_indent();
    if (!rl_point) return 0;

    int i = line_start(rl_point), j = rl_point, k;
    if (!i || rl_point <= i + prompt_length) goto backspace;
    for (k = i; k < rl_point; k++)
        if (rl_line_buffer[k] != ' ') goto backspace;


    k = i + prompt_length;
    do { rl_point--; } while ((rl_point - k) % tab_width);
    goto finish;

backspace:
    rl_point = (i == 0 || rl_point-i > prompt_length) ? rl_point-1 : i-1;

finish:
    rl_delete_text(rl_point, j);
    return 0;
}

scroll_input(int n)
{
    if (n > isize) {
        clear_lines(in_top, lines);
        iendy = in_top;
    } else if (delete_line) {
        xy(1, in_top);
        for (iendy = lines + 1; iendy > lines - n + 1; iendy--)
            tp(delete_line);
    } else if (has_scroll_region) {
        setscroll(in_top, lines);
        xy(1, lines);
        crnl(n);
        iendy = lines - n + 1;
    }
    xy(iendx = 1, iendy);
}

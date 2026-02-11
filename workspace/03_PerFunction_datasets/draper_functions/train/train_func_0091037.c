remember_boxes(unsigned level, WINDOW *txt_win, WINDOW *box_win)
{
    unsigned need = (level + 1) * 2;

    assert(level < COLS);

    if (winstack == 0) {
	len_winstack = 20;
	winstack = typeMalloc(WINSTACK, len_winstack);
    } else if (need >= len_winstack) {
	len_winstack = need;
	winstack = typeRealloc(WINSTACK, len_winstack, winstack);
    }
    winstack[level].text = txt_win;
    winstack[level].frame = box_win;
}

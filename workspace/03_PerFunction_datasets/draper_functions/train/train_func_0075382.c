set_color(char *my_pairs, int fg, int bg)
{
    int pair = (fg * COLORS) + bg;
    if (!my_pairs[pair]) {
	init_pair(pair, fg, bg);
    }
    attron(COLOR_PAIR(pair));
}

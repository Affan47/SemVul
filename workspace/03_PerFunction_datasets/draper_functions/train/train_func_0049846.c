draw_row(int y, int sel, int top, int sbtop, int sbbot)
{
    int i = (y - 4 - VSHIFT) + top;
    int dis = (i < cm->nentries) && is_disabled(cm->menu_entries[i]);

    printf("\033[%d;%dH\1#1\016x\017%s ",
	   y, MARGIN + 1 + HSHIFT,
	   (i == sel) ? "\1#5" : dis ? "\2#17" : "\1#3");

    if (i >= cm->nentries) {
	fputs(pad_line("", 0, WIDTH - 2 * MARGIN - 4), stdout);
    } else {
	display_entry(cm->menu_entries[i],
		      (i == sel) ? "\1#5" : dis ? "\2#17" : "\1#3",
		      (i == sel) ? "\1#6" : dis ? "\2#17" : "\1#4",
		      WIDTH - 2 * MARGIN - 4);
    }

    if (cm->nentries <= MENU_ROWS) {
	printf(" \1#1\016x\017");
    } else if (sbtop > 0) {
	if (y >= sbtop && y <= sbbot)
	    printf(" \1#7\016a\017");
	else
	    printf(" \1#1\016x\017");
    } else {
	putchar(' ');
    }
}

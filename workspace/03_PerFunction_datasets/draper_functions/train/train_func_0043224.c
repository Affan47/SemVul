show_panels(PANEL * px[MAX_PANELS + 1])
{
    static const char *help[] =
    {
	"",
	"Commands are letter/digit pairs.  Digits are the panel number.",
	"",
	"  b - put the panel on the bottom of the stack",
	"  c - create the panel",
	"  d - delete the panel",
	"  h - hide the panel",
	"  m - move the panel (M for continuous move)",
	"  r - resize the panel",
	"  s - show the panel",
	"  b - put the panel on the top of the stack"
    };

    struct {
	bool valid;
	bool hidden;
	PANEL *above;
	PANEL *below;
    } table[MAX_PANELS + 1];

    WINDOW *win;
    PANEL *pan;
    int j;

    for (j = 1; j <= MAX_PANELS; ++j) {
	table[j].valid = (px[j] != 0);
	if (table[j].valid) {
	    table[j].hidden = panel_hidden(px[j]);
	    table[j].above = panel_above(px[j]);
	    table[j].below = panel_below(px[j]);
	}
    }

    if ((win = newwin(LINES - 1, COLS, 0, 0)) != 0) {
	keypad(win, TRUE);
	if ((pan = new_panel(win)) != 0) {
	    werase(win);
	    mvwprintw(win, 0, 0, "Panels:\n");
	    for (j = 1; j <= MAX_PANELS; ++j) {
		if (table[j].valid) {
		    wprintw(win, " %d:", j);
		    if (table[j].hidden) {
			waddstr(win, " hidden");
		    } else {
			if (table[j].above) {
			    wprintw(win, " above %d",
				    which_panel(px, table[j].above));
			}
			if (table[j].below) {
			    wprintw(win, "%s below %d",
				    table[j].above ? "," : "",
				    which_panel(px, table[j].below));
			}
		    }
		    waddch(win, '\n');
		}
	    }
	    for (j = 0; j < (int) SIZEOF(help); ++j) {
		if (wprintw(win, "%s\n", help[j]) == ERR)
		    break;
	    }
	    wgetch(win);
	    del_panel(pan);
	    pflush();
	}
	delwin(win);
    }
}

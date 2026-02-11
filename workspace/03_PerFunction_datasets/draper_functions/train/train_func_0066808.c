set_busy(int interruptible)
{
    if (global.busy) {
	fputs("knews: internal error: set_busy when already busy!\n", stderr);
	return;
    }

    global.busy = True;

    XDefineCursor(display, XtWindow(main_widgets.shell), global.busy_cursor);
    if (main_widgets.second_shell)
	XDefineCursor(display, XtWindow(main_widgets.second_shell),
		      global.busy_cursor);
    set_busy_save(True);
    set_busy_search(True);

    if (interruptible)
	KnappSetSensitive(main_widgets.knapp[9], True);

    KnappSetActive(main_widgets.knapp[0], False);
    KnappSetActive(main_widgets.knapp[1],
		   global.mode == NewsModeGroup ||
		   global.mode == NewsModeThread);
    KnappSetActive(main_widgets.knapp[2], False);
    KnappSetActive(main_widgets.knapp[3], False);
    KnappSetActive(main_widgets.knapp[4], False);
    KnappSetActive(main_widgets.knapp[6], False);
    KnappSetActive(main_widgets.knapp[7], False);
    KnappSetActive(main_widgets.knapp[8], False);
    KnappSetActive(main_widgets.knapp[11], global.mode != NewsModeAllgroups);
    ArtTreeSetActive(main_widgets.arttree, False);
    ScrListSetActive(main_widgets.group_list, False);
    ScrListSetActive(main_widgets.thread_list, False);

    XFlush(display);
}

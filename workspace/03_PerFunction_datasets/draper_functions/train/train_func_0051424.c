get_yes_or_no(void)
{
    char *cx;
	char commandbuf[256];
    int gotline;
    event_t ev;

    status_line();


    while (1) {
		if (inputwin == promptwin) {
			glk_window_clear(promptwin);
			jacl_set_window(inputwin);
		}

		write_text(cstring_resolve("YES_OR_NO")->value);
		jacl_set_window(mainwin);

        glk_request_line_event(inputwin, commandbuf, 255, 0);

        gotline = FALSE;
        while (!gotline) {

            glk_select(&ev);

            switch (ev.type) {
                case evtype_LineInput:
                    if (ev.win == inputwin) {
                        gotline = TRUE;
                    }
                    break;

                case evtype_Arrange:
                    status_line();
                    break;
            }
        }

        commandbuf[ev.val1] = '\0';
        for (cx = commandbuf; *cx == ' '; cx++) { };


		*cx = tolower(*cx);

        if (*cx == cstring_resolve("YES_WORD")->value[0]) {
            return TRUE;
		} else if (*cx == cstring_resolve("NO_WORD")->value[0]) {
            return FALSE;
		}

    }
}

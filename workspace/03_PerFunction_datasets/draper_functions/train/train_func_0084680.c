get_string(char *string_buffer)
{
    char *cx;
	char commandbuf[256];
    int gotline;
    event_t ev;

    status_line();


	if (inputwin == promptwin) {
		glk_window_clear(promptwin);
		jacl_set_window(inputwin);
	}

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


	strncpy (string_buffer, cx, 255);
}

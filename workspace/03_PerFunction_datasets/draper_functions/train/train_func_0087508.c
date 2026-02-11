one_line_down(void)
{
	if ((messagesnr > 0) && (messagesmp) && (messagenr < (messagesnr - 1)))
	{
		draw_message_line(messageyp, messagenr, FALSE);

		messagenr++;

		if (messageyp >= (LINES - 3))
		{
			wrefresh(stdscr);
			scrollok(stdscr, TRUE);
			wscrl(stdscr, 1);
			scrollok(stdscr, FALSE);
		}
		else messageyp++;

		draw_message_line(messageyp, messagenr, TRUE);
	}
	else beep();
}

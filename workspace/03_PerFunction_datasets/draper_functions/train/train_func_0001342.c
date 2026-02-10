panels_can_be_displayed()
{
    if (tty_lines >= 7)
    {
	if (two_panel_mode)
	{
	    if (tty_columns >= 6 * 2)
		return ON;
	}
	else
	    if (tty_columns >= 6)
		return ON;
    }

    return OFF;
}

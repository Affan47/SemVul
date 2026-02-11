ui_backhelp(void)
{
    historypos--;
    if (historypos < 0)
	historypos = HISTORYSIZE - 1;
    ui_build_help(ui_helppage[historypos]);
}

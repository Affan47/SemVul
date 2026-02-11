do_auto_scroll()
{
	static CMD *scrup = 0;
	static CMD *scrdn = 0;
	static CMD *drag = 0;
	if (!scrup) {
		scrup = findcmd(USTR "upslide");
		scrdn = findcmd(USTR "dnslide");
		drag = findcmd(USTR "defmdrag");
	}
	if (auto_scroll > 0)
		execmd(scrdn,0);
	else if (auto_scroll < 0)
		execmd(scrup,0);

	execmd(drag,0);

	reset_trig_time();
}

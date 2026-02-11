hilite_screen()
{
	struct scrpos scrpos;

	get_scrpos(&scrpos);
	if (scrpos.pos == NULL_POSITION)
		return;
	prep_hilite(scrpos.pos, position(BOTTOM_PLUS_ONE), -1);
	repaint_hilite(1);
}

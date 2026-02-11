black_promotion (gshort from, gshort to)
{
	register Square new_to;
	register gshort i;

	for (i = 2; i < 6; i++) {
		new_to = 128 + 8 * i + to - A1;
		new_capture_move (from, new_to);
	}
}

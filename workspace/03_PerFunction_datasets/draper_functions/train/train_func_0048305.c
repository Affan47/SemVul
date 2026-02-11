do_axis_part(int axis, bool craxis, int xset) throw (ParserError) {


	switch (xset) {
	  case GLEG_CMD_AXIS:
		do_axis(axis, craxis);
		do_labels(axis, false);
		do_side(axis, false);
		do_ticks(axis, false);
		break;
	  case GLEG_CMD_LABELS:
		do_labels(axis, true);
		break;
	  case GLEG_CMD_SIDE:
		do_side(axis, true);
		break;
	  case GLEG_CMD_TICKS:
		do_ticks(axis, true);
		break;
	  case GLEG_CMD_SUBTICKS:
		do_subticks(axis, true);
		break;
	}
}

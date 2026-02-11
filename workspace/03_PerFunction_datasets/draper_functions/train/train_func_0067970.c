ed_move_to_end(EditLine *el, Int c __attribute__((__unused__)))
{

	el->el_line.cursor = el->el_line.lastchar;
	if (el->el_map.type == MAP_VI) {
		if (el->el_chared.c_vcmd.action != NOP) {
			cv_delfini(el);
			return (CC_REFRESH);
		}
#ifdef VI_MOVE
		el->el_line.cursor--;
#endif
	}
	return (CC_CURSOR);
}

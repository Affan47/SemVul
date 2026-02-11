parse_range(char **cmd) {
	Text *txt = vis->win->text->data;
	Filerange r = text_range_empty();
	Mark *marks = vis->win->text->marks;
	switch (**cmd) {
	case '%':
		r.start = 0;
		r.end = text_size(txt);
		(*cmd)++;
		break;
	case '*':
		r.start = text_mark_get(txt, marks[MARK_SELECTION_START]);
		r.end = text_mark_get(txt, marks[MARK_SELECTION_END]);
		(*cmd)++;
		break;
	default:
		r.start = parse_pos(cmd);
		if (**cmd != ',')
			return r;
		(*cmd)++;
		r.end = parse_pos(cmd);
		break;
	}
	return r;
}

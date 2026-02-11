canvas_frame_drop(struct frame *frame, int x, int y)
{
	struct coord pos = canvas_to_coord(x, y);

	if (!tool_place_frame(frame, pos))
		return FALSE;
	change_world();
	return TRUE;
}

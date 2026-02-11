destroy_frame(struct frame *frame)
{
	while (frame->tables) {
		delete_table(frame->tables);
		destroy();
	}
	while (frame->loops) {
		delete_loop(frame->loops);
		destroy();
	}
	while (frame->vecs) {
		delete_vec(frame->vecs);
		destroy();
	}
	while (frame->objs) {
		delete_obj(frame->objs);
		destroy();
	}
	free(frame);
}

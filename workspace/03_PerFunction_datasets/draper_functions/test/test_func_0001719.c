reverse_frames(FILE *file, struct frame *last)
{
	if (last) {
		reverse_frames(file, last->next);
		dump_frame(file, last, "\t");
	}
}

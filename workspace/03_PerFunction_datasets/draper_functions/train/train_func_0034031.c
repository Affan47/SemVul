frame_free(frame)
    struct FRAME *frame;
{
    struct FRAME *tmp;

    if (frame->argc > 0 && (frame->flags & FRAME_MALLOC))
        free(frame->argv);
    frame = frame->prev;
    while (frame) {
	if (frame->argc > 0 && (frame->flags & FRAME_MALLOC))
	    free(frame->argv);
	tmp = frame;
	frame = frame->prev;
	free(tmp);
    }
}

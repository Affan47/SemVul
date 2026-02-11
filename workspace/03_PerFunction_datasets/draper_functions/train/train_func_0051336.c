playout_restart(playout_state_t *s, int min_length, int max_length)
{
    playout_frame_t *frame;
    playout_frame_t *next;


    for (frame = s->free_frames;  frame;  frame = next)
    {
        next = frame->later;
        free(frame);
    }

    memset(s, 0, sizeof(*s));
    s->dynamic = (min_length < max_length);
    s->min_length = min_length;
    s->max_length = (max_length > min_length)  ?  max_length  :  min_length;
    s->dropable_threshold = 1*0x10000000/100;
    s->start = TRUE;
    s->since_last_step = 0x7FFFFFFF;

    s->actual_buffer_length =
    s->target_buffer_length = (s->max_length - s->min_length)/2;
}

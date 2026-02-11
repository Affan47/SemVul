flush_input(tqueue * tq, int show_messages)
{
    if (tq->first_input) {
	Stream *s = new_stream(100);
	task *t;

	if (show_messages)
	    notify(tq->player, ">> Flushing the following pending input:");
	while ((t = dequeue_input_task(tq, DQ_FIRST)) != 0) {

	    if (show_messages) {
		stream_printf(s, ">>     %s", t->t.input.string);
		notify(tq->player, reset_stream(s));
	    }
	    free_task(t, 1);
	}
	if (show_messages)
	    notify(tq->player, ">> (Done flushing)");
    } else if (show_messages)
	notify(tq->player, ">> No pending input to flush...");
}

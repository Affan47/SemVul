event_free(struct event *ev)
{
	_event_debug_assert_is_setup(ev);


	event_del(ev);
	_event_debug_note_teardown(ev);
	mm_free(ev);

}

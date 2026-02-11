clear () throw ()
{
	while (!action_queue.empty ())
		action_queue.pop ();
}

queue (const Action& action, bool idempotent) throw ()
{
	if (idempotent) clear ();
	action_queue.push (action);
	update (true);
}

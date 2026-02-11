run_all () throw ()
{
	while (!action_queue.empty ())
	{
		try
		{
			action_queue.front () ();
		}
		catch (...) {}
		action_queue.pop ();
	}
}

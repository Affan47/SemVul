unlocked_eval (double x)
{


	if (_dirty) {
		solve ();
	}

	return _list.unlocked_eval (x);
}

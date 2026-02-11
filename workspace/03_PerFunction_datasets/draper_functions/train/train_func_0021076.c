send_change (const PropertyChange& what_changed)
{
	if (what_changed.empty()) {
		return;
	}

	{
		Glib::Threads::Mutex::Lock lm (_lock);
		if (property_changes_suspended ()) {
			_pending_changed.add (what_changed);
			return;
		}
	}

	PropertyChanged (what_changed);
}

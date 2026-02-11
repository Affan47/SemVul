unregisterEvent(int event_id, Analyzer* const analyzer) {
	if (event_id < 0 || event_id >= (int) _events.size())
		return;
	vector<Analyzer*>& subscribers = _events[event_id];
	for (vector<Analyzer*>::iterator s = subscribers.begin(); s != subscribers.end(); ++s) {
		if (*s == analyzer) {
			subscribers.erase(s);
			Debug::event() << "Unregistered " << analyzer->name() << " for event " << event_id << endl;
			return;
		}
	}
	Debug::warning() << "Failed to unregister " << analyzer->name() << " for event " << event_id << endl;
}

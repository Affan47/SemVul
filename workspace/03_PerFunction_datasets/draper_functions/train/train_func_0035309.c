getPreviousLogentry()
{
	if (_it_entries == _entries->begin()) {

		if (_it_logs == g_store->logCache()->logfiles()->begin())
			return 0;
		else {
			_it_logs--;
			_entries = _it_logs->second->getEntriesFromQuery(_query, g_store->logCache(), _since, _until, CLASSMASK_STATEHIST);
			_it_entries = _entries->end();
		}
	}
	return (--_it_entries)->second;
}

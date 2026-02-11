getNextLogentry()
{
	if (++_it_entries == _entries->end()) {
		if (++_it_logs == g_store->logCache()->logfiles()->end()) {


			--_it_entries;
			--_it_logs;
			return 0;
		}
		else {
			_entries = _it_logs->second->getEntriesFromQuery(_query, g_store->logCache(), _since, _until, CLASSMASK_STATEHIST);
			_it_entries = _entries->begin();
		}
	}
	return _it_entries->second;
}

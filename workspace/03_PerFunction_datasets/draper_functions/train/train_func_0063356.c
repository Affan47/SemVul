dispatch_pending()
{
	_mutex_p.lock();


	while (_pending_queue.size() > 0)
	{
		Connection::PrivatePList::iterator i, j;

		i = _pending_queue.begin();

		while (i != _pending_queue.end())
		{
			j = i;

			++j;

			if ((*i)->do_dispatch())
				_pending_queue.erase(i);

			i = j;
		}
	}
	_mutex_p.unlock();
}

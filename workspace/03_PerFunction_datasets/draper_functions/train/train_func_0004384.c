remove (FileDescriptor* d)
{
	Glib::Threads::Mutex::Lock lm (_mutex);

	if (d->is_open ()) {
		close (d);
		DEBUG_TRACE (
			DEBUG::FileManager,
			string_compose ("closed file for %1; file is being removed; now have %2 of %3 open\n", d->_path, _open, _max_open)
			);
	}

	_files.remove (d);
}

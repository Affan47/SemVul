alloc ()
{
	void *ptr;

	if (!m_lock && (m_lock = new Glib::Mutex()) == 0) {
		fatal << "cannot create Glib::Mutex in pool.cc" << endmsg;

	}

	Glib::Mutex::Lock guard(*m_lock);
	ptr = Pool::alloc ();
	return ptr;
}

boost_debug_list_ptrs ()
{
	Glib::Threads::Mutex::Lock guard (the_lock());

	if (sptrs().empty()) {
		cerr << "There are no dangling shared ptrs\n";
	} else {
		for (PointerMap::iterator x = sptrs().begin(); x != sptrs().end(); ++x) {
			cerr << "Shared ptr @ " << x->first << " history: "
			     << *x->second
			     << endl;
		}
	}
}

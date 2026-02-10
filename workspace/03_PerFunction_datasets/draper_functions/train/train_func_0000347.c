flush ()
{
	if (good () && rdbuf ()) {
		if (rdbuf ()->pubsync () == EOF) {
			setstate (badbit);
		}
	}
	return (*this);
}

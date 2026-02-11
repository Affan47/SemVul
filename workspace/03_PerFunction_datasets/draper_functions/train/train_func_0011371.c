setStatus (bool go)
{
	if (go) {
		show ();
		m_movie->start ();
	} else {
		hide ();
		m_movie->stop ();
	}
}

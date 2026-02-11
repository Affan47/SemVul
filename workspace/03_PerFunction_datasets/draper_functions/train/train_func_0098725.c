parse_xml (const QByteArray &b, int id)
{
	LastFmHandler *x = dynamic_cast<LastFmHandler*> (m_xml.contentHandler ());
	QXmlInputSource s;
	s.setData (b);

	x->reset ();

	m_xml.parse (s);

	if (x->type () == LastFmHandler::SIMILARARTIST) {
		QList<LastFmArtist> l = x->artist_list ();
		m_cache[m_cache_map[id]] = l;
		emit gotData (m_cache_map[id]);
	}
	return true;
}

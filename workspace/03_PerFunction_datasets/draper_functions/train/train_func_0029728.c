operator<<(QDataStream& out, const OpeningBook* book)
{
	OpeningBook::Map::const_iterator it;
	for (it = book->m_map.constBegin(); it != book->m_map.constEnd(); ++it)
		book->writeEntry(it, out);

	return out;
}

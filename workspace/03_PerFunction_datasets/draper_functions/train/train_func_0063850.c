operator>>(QDataStream& in, OpeningBook* book)
{
	while (!in.status() != QDataStream::Ok)
		book->readEntry(in);

	return in;
}

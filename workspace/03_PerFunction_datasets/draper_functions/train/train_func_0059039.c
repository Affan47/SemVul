dot_truncate(const QString &in, int clip)
{
	if((int)in.length() <= clip)
		return in;
	QString s = in;
	s.truncate(clip);
	s += "...";
	return s;
}

clone() const
{
	mail::Header::plain *c=new plain(name, text);

	if (!c)
		throw strerror(errno);
	return c;
}

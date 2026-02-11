operator=(const mail::keywords::Message &m)
{
	++m.b->refCnt;

	if (--b->refCnt == 0)
		delete b;

	b=m.b;
	return *this;
}

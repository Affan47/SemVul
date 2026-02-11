socketWrite(string s)
{
	writtenFlag=true;

	WriteBuffer *w=new WriteBuffer;

	if (!w)
		LIBMAIL_THROW("Out of memory.");

	try {
		w->writebuffer=s;
		writequeue.push(w);
	} catch (...) {
		delete w;
		LIBMAIL_THROW(LIBMAIL_THROW_EMPTY);
	}
}

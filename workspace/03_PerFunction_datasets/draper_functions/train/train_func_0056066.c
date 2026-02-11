lyxbreaker(void const * data, const char * hint, int size)
{
	LYXERR0("break on pointer: " << data << " hint: " << hint
		<< " size: " << size);
	LASSERT(false, return);
}

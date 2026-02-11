uflow ()
{
	trace_with_mask("Streambuf::uflow",STRMBUFTRACE);

	if (underflow () == EOF)
		return EOF;
	dump ();
	return *(unsigned char *) m_read_ptr++;
}

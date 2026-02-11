operator>>(Socket& s_, xdrIOBuffer& b_)
{
	trace_with_mask("Socket >> xdrIOBuffer", XDRBUFTRACE);

	DL((XDRBUFTRACE,"Buffer Initially:\n"));
	b_.dump ();

	if (b_.m_state != xdrIOBuffer::waiting) {
		EL((ASSAERR,"Wrong state: %s\n", b_.get_state ().c_str ()));
		return s_;
	}
	int expected = b_.m_sz - b_.size ();

	DL((XDRBUFTRACE,"Bytes expected: %d\n",expected));
	DL((XDRBUFTRACE,"Bytes in Socket buffer(s): %d\n", s_.getBytesAvail ()));
	int ret;

	if ((ret = s_.read (b_.m_ptr, expected)) <= 0)
	{
#if defined(WIN32)
        if (WSAGetLastError () != WSAEWOULDBLOCK) {
			WSASetLastError (0);
			EL((ASSAERR,"Socket::read() error!\n"));
			b_.m_state = xdrIOBuffer::error;
		}
#else
		if (errno != EWOULDBLOCK) {
			EL((ASSAERR,"Socket::read() error!\n"));
			b_.m_state = xdrIOBuffer::error;
		}
#endif
		else {
			EL((ASSAERR,"Socket::read() error! \n"));
		}
		return s_;
	}
	b_.m_ptr += ret;

	DL((XDRBUFTRACE,"Received %d bytes\n", ret));
	b_.dump ();

	if (b_.m_sz == b_.size ()) {
		DL((XDRBUFTRACE,"Complete message is in the buffer!\n"));
		b_.m_state = xdrIOBuffer::xmitted;
		b_.m_ptr = b_.m_buf;
		b_.dump ();
	}
	return s_;
}

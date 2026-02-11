dump () const
{
	trace_with_mask("xdrIOBuffer::dump", XDRBUFTRACE);

	DL((XDRBUFTRACE,"xdrIOBuffer->this = 0x%x\n", long(this) ));
	DL((XDRBUFTRACE,"\n\n" \
	    "\tm_buf ........: 0x%x \n" \
	    "\tm_sz .........: %d   \n" \
	    "\tm_ptr ........: 0x%x \n" \
	    "\tbytes left ...: %d   \n" \
	    "\tm_state ......: %s   \n\n",
	    long (m_buf), m_sz, long (m_ptr),(m_sz - size ()),
	    get_state ().c_str ()));

	if (m_ptr != m_buf) {
		MemDump image (m_buf, size ());
		DL((XDRBUFTRACE,"Bytes in buffer so far:\n\n%s\n\n",
		    image.getMemDump () ));
	}
	else if (m_ptr == m_buf && m_state == xmitted) {
		MemDump image (m_buf, (m_sz));
		DL((XDRBUFTRACE,"Complete buffer:\n\n%s\n\n",
			image.getMemDump () ));
	}
	else {
		DL((XDRBUFTRACE,"Empty buffer\n" ));
	}
}

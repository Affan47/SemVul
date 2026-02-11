DefaultRead(int timeout)
{
	if( m_seen_usb_error && timeout == -1 ) {


		timeout = 0;
	}


	Data *buf = m_default.wait_pop(timeout == -1 ? m_timeout : timeout);
	return DataHandle(*this, buf);
}

JAVAD_sendMessage(const char *str, bool waitForAnswer )
{
	if (!str) return;
	const size_t len = strlen(str);
	CSerialPort *stream_serial = dynamic_cast<CSerialPort*>(m_data_stream);
	if (!stream_serial) return;

	size_t written;

	{
		CCriticalSectionLocker lock( m_data_stream_cs);
		written = stream_serial->Write(str,len);
	}

	if (m_verbose)
		std::cout << "[CGPSInterface] TX: " << str;

	if (written != len )
		throw std::runtime_error(format("Error sending command: '%s'",str).c_str());
	mrpt::system::sleep(5);

	if (!waitForAnswer) return;

	mrpt::system::sleep(200);
	char buf[200];
	buf[0]='\0';

	int bad_counter = 0;
	while(bad_counter < 10)
	{
		size_t nRead;
		{
			CCriticalSectionLocker lock( m_data_stream_cs);
			written = stream_serial->Write(str,len);
			nRead = stream_serial->Read(buf,sizeof(buf));
		}

		if (m_verbose)
			std::cout << "[CGPSInterface] RX: " << buf << std::endl;

		if (nRead<3 )
			throw std::runtime_error(format("ERROR: Invalid response '%s' for command '%s'",buf,str));

		if (nRead>=3 && buf[0]=='R' && buf[1]=='E')
			return;
		else
			++bad_counter;
	}
	throw std::runtime_error(format("ERROR: Invalid response '%s' for command '%s'",buf,str));
}

gs_output(const char* buffer, int len)
{
	m_Output.append(QString::fromLocal8Bit(buffer, len));
	return len;
}

CopyRangeTo2(BufferedTransformation &target, lword &begin, lword end, const std::string &channel, bool blocking) const
{
	if (m_definiteLength)
		end = STDMIN(m_length, end);
	return m_inQueue.CopyRangeTo2(target, begin, end, channel, blocking);
}

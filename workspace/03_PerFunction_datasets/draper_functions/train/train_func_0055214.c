FlushOutputQueues()
{
	for (unsigned int i=0; i<m_outputChannelIds.size(); i++)
		m_outputQueues[i].TransferAllTo(*AttachedTransformation(), m_outputChannelIdStrings[i]);
}

ProcessInputQueues()
{
	bool finished = (m_channelsFinished == m_threshold);
	int i;

	while (finished ? m_channelsReady > 0 : m_channelsReady == m_threshold)
	{
		m_channelsReady = 0;
		for (i=0; i<m_threshold; i++)
		{
			MessageQueue &queue = m_inputQueues[i];
			queue.GetWord32(m_y[i]);

			if (finished)
				m_channelsReady += queue.AnyRetrievable();
			else
				m_channelsReady += queue.NumberOfMessages() > 0 || queue.MaxRetrievable() >= 4;
		}

		for (i=0; (unsigned int)i<m_outputChannelIds.size(); i++)
		{
			if (m_outputToInput[i] != m_threshold)
				m_outputQueues[i].PutWord32(m_y[m_outputToInput[i]]);
			else if (m_v[i].size() == m_threshold)
				m_outputQueues[i].PutWord32(BulkPolynomialInterpolateAt(field, m_y.begin(), m_v[i].begin(), m_threshold));
			else
			{
				m_u.resize(m_threshold);
				PrepareBulkPolynomialInterpolationAt(field, m_u.begin(), m_outputChannelIds[i], &(m_inputChannelIds[0]), m_w.begin(), m_threshold);
				m_outputQueues[i].PutWord32(BulkPolynomialInterpolateAt(field, m_y.begin(), m_u.begin(), m_threshold));
			}
		}
	}

	if (m_outputChannelIds.size() > 0 && m_outputQueues[0].AnyRetrievable())
		FlushOutputQueues();

	if (finished)
	{
		OutputMessageEnds();

		m_channelsReady = 0;
		m_channelsFinished = 0;
		m_v.clear();

		vector<MessageQueue> inputQueues;
		vector<word32> inputChannelIds;

		inputQueues.swap(m_inputQueues);
		inputChannelIds.swap(m_inputChannelIds);
		m_inputChannelMap.clear();
		m_lastMapPosition = m_inputChannelMap.end();

		for (i=0; i<m_threshold; i++)
		{
			inputQueues[i].GetNextMessage();
			inputQueues[i].TransferAllTo(*AttachedTransformation(), WordToString(inputChannelIds[i]));
		}
	}
}

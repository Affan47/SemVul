UncheckedSetKey(const byte *key, unsigned int keyLen, const NameValuePairs &params)
{
	AssertValidKeyLength(keyLen);

	m_x = 1;
	m_y = 0;

	unsigned int i;
	for (i=0; i<256; i++)
		m_state[i] = i;

	unsigned int keyIndex = 0, stateIndex = 0;
	for (i=0; i<256; i++)
	{
		unsigned int a = m_state[i];
		stateIndex += key[keyIndex] + a;
		stateIndex &= 0xff;
		m_state[i] = m_state[stateIndex];
		m_state[stateIndex] = a;
		if (++keyIndex >= keyLen)
			keyIndex = 0;
	}

	int discardBytes = params.GetIntValueWithDefault("DiscardBytes", GetDefaultDiscardBytes());
	DiscardBytes(discardBytes);
}

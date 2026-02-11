getPushedKey(mrptKeyModifier *out_pushModifier)
{
	int k = 0;
	if (out_pushModifier) *out_pushModifier = MRPTKMOD_NONE;

	for (;;)
	{
		if (m_keyPushed)
		{
			k=m_keyPushedCode;
			m_keyPushed=false;
			if (out_pushModifier) *out_pushModifier = m_keyPushedModifier;
			return k;
		}
		mrpt::system::sleep(10);

		if (!isOpen())
			return 0;
	}
}

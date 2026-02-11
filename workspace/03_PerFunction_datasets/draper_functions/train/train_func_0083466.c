FirstPut(const byte *inString)
{
	if (m_flags & HASH_AT_BEGIN)
	{
		m_expectedHash.New(m_digestSize);
		memcpy(m_expectedHash, inString, m_expectedHash.size());
		if (m_flags & PUT_HASH)
			AttachedTransformation()->Put(inString, m_expectedHash.size());
	}
}

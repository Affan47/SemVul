TruncatedFinal(byte *mac, size_t size)
{
	ThrowIfInvalidTruncatedSize(size);

	if (m_counter)
		ProcessBuf();

	memcpy(mac, m_reg, size);
	memset(m_reg, 0, AccessCipher().BlockSize());
}

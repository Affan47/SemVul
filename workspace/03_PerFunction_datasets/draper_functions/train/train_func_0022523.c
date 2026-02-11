checkForReady()
{
	if (m_status != CAdunanzAStreaming::Requested) return;

	if (!m_pTargetFile) return;


	if (!m_pTargetFile->PreviewAvailable()) return;


	m_requiredParts = 1 + (uint16) (0.01f * thePrefs::ADU_GetBufferStreamingPercentageThreshold() * m_pTargetFile->GetPartCount());

	if (getLastConsecutiveCompletePart() >= m_requiredParts) {
		m_status = CAdunanzAStreaming::Ready;
	}

}

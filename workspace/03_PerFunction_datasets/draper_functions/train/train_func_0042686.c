GetSampleSize() const
{
    return (m_bIsAudio) ? m_Header.hdr.aud.wfx.nBlockAlign : 0;
}

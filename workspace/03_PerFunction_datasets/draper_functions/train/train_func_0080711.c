CreateCompressor (unsigned int RasterSize)
{
    m_pCompressor = new ModeDeltaPlus (pSS, this, RasterSize);
	return m_pCompressor;
}

FixAvgBytes(uint_t bps)
{
    if (bps > 8000)
    {
	m_dFrameRate = bps;
	return 0;
    }


    return -1;
}

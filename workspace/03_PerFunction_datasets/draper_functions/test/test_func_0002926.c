getLastWindowImage( mrpt::utils::CImage &out_img ) const
{
	bool ret;

	{
		mrpt::synch::CCriticalSectionLocker	lock(& m_last_captured_img_cs );
		if (m_last_captured_img)
		{
			out_img = *m_last_captured_img;
			ret = true;
		}
		else ret = false;
	}
	return ret;
}

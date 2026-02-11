drawImage(
	int						x,
	int						y,
	const CImage	&img
	)
{
    MRPT_TRY_START;

    ((CImage*)m_hdc.get())->drawImage(x,y,img);

    MRPT_TRY_END;
}

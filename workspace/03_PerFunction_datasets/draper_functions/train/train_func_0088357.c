RightJustify( long nNewLength, char fill , bool  )
{
	CString s;

	while( (s.m_nStringLength+m_nStringLength) < nNewLength )
		s+=fill;

	return(s+*this);
}

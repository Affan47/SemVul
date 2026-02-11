Compare( const char * other ) const
{
	if ( m_nStringLength == 0 )
	{
		if ( other == NULL )
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else if ( other == NULL )
	{
		return -1;
	}
	else
	{
		return strcoll( Data(), other );
	}
}

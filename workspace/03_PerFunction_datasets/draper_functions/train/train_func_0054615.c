transposed() const
{
	Matrix4f out;
	for( int i = 0; i < 4; ++i )
	{
		for( int j = 0; j < 4; ++j )
		{
			out( j, i ) = ( *this )( i, j );
		}
	}

	return out;
}

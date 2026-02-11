FindDirectoryEntry ( FOURCC type, int n ) const
{
	int i, j = 0;
	int count = directory.size();

	for ( i = 0; i < count; ++i )
		if ( directory[ i ].type == type )
		{
			if ( j == n )
				return i;
			j++;
		}

	return -1;
}

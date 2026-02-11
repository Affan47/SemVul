PrintDirectory() const
{
	int i;
	int count = directory.size();

	for ( i = 0; i < count; ++i )
		PrintDirectoryEntry( i );
}

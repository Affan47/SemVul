AddDirectoryEntry( FOURCC type, FOURCC name, off_t length, int list )
{


	RIFFDirEntry entry( type, name, length, 0 , list );


	if ( list != RIFF_NO_PARENT )
	{
		RIFFDirEntry parent = GetDirectoryEntry( list );
		entry.offset = parent.offset + parent.length + RIFF_HEADERSIZE;
	}


	while ( list != RIFF_NO_PARENT )
	{
		RIFFDirEntry parent = GetDirectoryEntry( list );
		parent.length += RIFF_HEADERSIZE + length;
		SetDirectoryEntry( list, parent );
		list = parent.parent;
	}

	directory.insert( directory.end(), entry );

	return directory.size() - 1;
}

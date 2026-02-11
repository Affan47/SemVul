write_ptr_array(File* filePtr, int objectSize)
{
	int   i;
	char* elePtr;

	filePtr->file_put_short( size() );

	for( i=1; i<=size() ; i++ )
	{
		elePtr = (char*) get_ptr(i);


		if( !elePtr )
		{
			filePtr->file_put_short(0);
		}
		else
		{
			filePtr->file_put_short(1);

			if( !filePtr->file_write(elePtr, objectSize) )
				return 0;
		}
	}


	write_empty_room(filePtr);

	return 1;
}

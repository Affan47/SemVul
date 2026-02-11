write_file(File* filePtr)
{
	file_ptr = filePtr;


	if( game_file_array.demo_format )
		filePtr->file_put_short( -GAME_VERSION );
	else
		filePtr->file_put_short( GAME_VERSION );


	if( game_file_array.demo_format )
	{
		if( !write_file_1(filePtr) )
			return 0;

		if( !write_file_2(filePtr) )
			return 0;
	}
	else
	{
		if( !write_file_2(filePtr) )
			return 0;

		if( !write_file_1(filePtr) )
         return 0;
   }

   if( !write_file_3(filePtr) )
		return 0;

   return 1;
}

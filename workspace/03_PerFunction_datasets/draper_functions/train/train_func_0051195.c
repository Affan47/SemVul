read_file(File* filePtr)
{
	file_ptr = filePtr;


	int originalRandomSeed = misc.get_random_seed();

	game_file_array.load_file_game_version = filePtr->file_get_short();


	if( game_file_array.demo_format && game_file_array.load_file_game_version > 0
		|| !game_file_array.demo_format && game_file_array.load_file_game_version < 0)
		return -1;


	game_file_array.load_file_game_version = abs(game_file_array.load_file_game_version);

	if(game_file_array.load_file_game_version > GAME_VERSION)
		return -1;


	game_file_array.same_version = ( game_file_array.load_file_game_version/100==GAME_VERSION/100 );


	if( game_file_array.demo_format )
	{
		if( !read_file_1(filePtr) )
			return 0;

		if( !read_file_2(filePtr) )
			return 0;
	}
	else
	{
		if( !read_file_2(filePtr) )
			return 0;

		if( !read_file_1(filePtr) )
			return 0;
	}

	if( !read_file_3(filePtr) )
		return 0;


	err_when( originalRandomSeed != misc.get_random_seed() );

	misc.set_random_seed(loaded_random_seed);

	return 1;
}

cf_free_secondary_filelist()
{
	int i;


	for (i=0; i<CF_MAX_ROOT_BLOCKS; i++ )	{
		if ( Root_blocks[i] )	{
			vm_free( Root_blocks[i] );
			Root_blocks[i] = NULL;
		}
	}
	Num_roots = 0;


	for (i=0; i<CF_MAX_FILE_BLOCKS; i++ )	{
		if ( File_blocks[i] )	{
			vm_free( File_blocks[i] );
			File_blocks[i] = NULL;
		}
	}
	Num_files = 0;
}

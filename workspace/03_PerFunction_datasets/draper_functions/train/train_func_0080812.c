ijmlist_idx_dump(jmlist jml)
{

	printf("capacity: %u, usage: %u\n",jml->idx_list.capacity,jml->idx_list.usage);


	if( jml->idx_list.usage )
	{
		printf("list of entries: \n");
		jmlist_index i;
		for( i = 0 ; i < jml->idx_list.capacity ; i++ )
			printf("%u %p\n",i,jml->idx_list.plist[i]);
	}

	return JMLIST_ERROR_SUCCESS;
}

Dispose_StatTable() {
unsigned int i, hash_num;

	if ( !initialised )
		return;

	for ( hash_num=0; hash_num<NumStats; hash_num++ ) {
		free((void *)StatTable[hash_num].bucket);
		for ( i=0; i<StatTable[hash_num].NumBlocks; i++ )
			free((void *)StatTable[hash_num].memblock[i]);
		free((void *)StatTable[hash_num].memblock);
	}

}

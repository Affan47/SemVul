fat_getFreeCluster(Volume_t *V) {
	DWORD val;
    if (V->FatType == FAT32) {
        val= fat32_getFreeCluster(V);
    } else {
		val= fat16_getFreeCluster(V);
    }

	fprintf(stderr,"- - fat_getFreeCluster: clus: %u; freecnt: %u\n",val,V->freecnt);
	return val;
}

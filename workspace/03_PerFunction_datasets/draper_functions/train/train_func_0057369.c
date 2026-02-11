fat32_getFreeCluster(Volume_t *V) {
	int res;
	DWORD clus;

	while (V->fstfclus >= V->fclusz) {
		res = fat_populate_freelist(V);
		if (res <= 0) {
			fprintf(stderr,"populate freelist error: end of space on the volume\n");
			return (DWORD) 0;
		}
	}

	clus = V->freeclus[V->fstfclus];
	V->freecnt--;
	V->fstfclus++;
	V->nextfree = MAX(clus,V->nextfree);
	if (clus > (V->DataClusters + 1)) {
		fprintf(stderr,"getFreeCluster() error. clus num : %u, max clus: %u\n", clus, (V->DataClusters + 1));
		return 0;
	}

	return clus;
}

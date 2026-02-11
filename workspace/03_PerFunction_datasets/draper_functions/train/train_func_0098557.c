statAfterCompact(int myGeneration) {
	int i;
	for(i = 0;i<=myGeneration;i++){
		stats[i] -= myAllocators[i]->getFreeSize();
		if(stats[i] != 0){
			fprintf(stderr,"ERROR(Line %d):compact incosistency %d bytes for gen %d\n",
					gLineInTrace, stats[i],i);
		}
	}

}

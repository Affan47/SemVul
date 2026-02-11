calcFileBlockOffset(oleEntry *e, long int blk) {
	long int res;
	if ( e->isBigBlock ) {
		res=512+e->blocks[blk]*sectorSize;
	} else {
		long int sbdPerSector=sectorSize/shortSectorSize;
		long int sbdSecNum=e->blocks[blk]/sbdPerSector;
		long int sbdSecMod=e->blocks[blk]%sbdPerSector;


		res=512 + rootEntry->blocks[sbdSecNum]*sectorSize + sbdSecMod*shortSectorSize;
	}
	return res;
}

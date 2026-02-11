ole_seek(FILE *stream, long offset, int whence) {
	oleEntry *e=(oleEntry*)stream;
	long int new_ole_offset=0, new_file_offset;
	int ssize, modBlock, blockNumber;

	switch(whence) {
	case SEEK_SET:
		new_ole_offset=offset;
		break;

	case SEEK_CUR:
		new_ole_offset=e->ole_offset+offset;
		break;

	case SEEK_END:
		new_ole_offset=e->length+offset;
		break;

	default:
		errno=EINVAL;
		return -1;
	}
	if(new_ole_offset<0)
		new_ole_offset=0;
	if(new_ole_offset >= e->length)
		new_ole_offset=e->length;

	ssize = (e->isBigBlock ? sectorSize : shortSectorSize);
	blockNumber=new_ole_offset/ssize;
	if ( blockNumber >= e->numOfBlocks )
		return -1;

	modBlock=new_ole_offset%ssize;
	new_file_offset = calcFileBlockOffset(e,blockNumber)+modBlock;
	fseek(e->file, e->file_offset=new_file_offset, SEEK_SET);
	e->ole_offset=new_ole_offset;

	return 0;
}

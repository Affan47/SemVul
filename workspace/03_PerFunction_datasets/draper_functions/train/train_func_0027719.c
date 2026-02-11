attrKeyWrite(off_t offset, BTKey* toWrite, io_func* io) {
	HFSPlusAttrKey* key;
	uint16_t keyLength;
	uint16_t nodeNameLength;
	int i;

	keyLength = toWrite->keyLength;
	key = (HFSPlusAttrKey*) malloc(keyLength);
	memcpy(key, toWrite, keyLength);

	nodeNameLength = key->name.length;

	FLIPENDIAN(key->keyLength);
	FLIPENDIAN(key->fileID);
	FLIPENDIAN(key->startBlock);
	FLIPENDIAN(key->name.length);

	for(i = 0; i < nodeNameLength; i++) {
		FLIPENDIAN(key->name.unicode[i]);
	}

	if(!WRITE(io, offset, keyLength, key))
		return FALSE;

	free(key);

	return TRUE;
}

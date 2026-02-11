dbzstore(key, data)
datum key;
datum data;
{
	char buffer[DBZMAXKEY + 1];
	datum mappedkey;
	register size_t keysize;

	DEBUG(("dbzstore: (%s)\n", key.dptr));


	keysize = key.dsize;
	if (keysize >= DBZMAXKEY) {
		DEBUG(("dbzstore: key size too big (%d)\n", key.dsize));
		return(-1);
	}

	mappedkey.dptr = mapcase(buffer, key.dptr, keysize);
	buffer[keysize] = '\0';
	mappedkey.dsize = keysize;

	return(store(mappedkey, data));
}

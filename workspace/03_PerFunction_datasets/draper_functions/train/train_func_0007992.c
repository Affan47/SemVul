keyGetFullName(const Key *key, char *returnedName, size_t maxSize)
{
	size_t userSize=sizeof("user")-1;
	size_t ownerSize;
	ssize_t length;
	char *cursor;

	if (!key) return -1;
	if (!returnedName) return -1;
	if (!maxSize) return -1;

	if (maxSize > SSIZE_MAX) return -1;

	length=keyGetFullNameSize(key);
	if (length == 1) {

		returnedName[0]=0;
		return length;
	}
	else if (length < 0) return length;
	else if (length > maxSize) {

		return -1;
	}

	cursor=returnedName;
	if (keyIsUser(key))
	{
		strncpy(cursor,key->key,userSize);
		cursor+=userSize;
		if (key->owner) {
			*cursor=':'; ++cursor;
			ownerSize=kdbiStrLen(key->owner)-1;
			strcpy(cursor,key->owner);
			cursor+=ownerSize;
		}
		strcpy(cursor,key->key+userSize);
	} else strcpy(cursor,key->key);

	return length;
}

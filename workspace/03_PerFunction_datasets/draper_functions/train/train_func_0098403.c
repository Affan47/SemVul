keySetOwner(Key *key, const char *owner)
{
	if (!key) return -1;

	if (owner && (key->ownerSize=kdbiStrLen(owner)) > 1)
	{
		if (key->owner) {
			char *p=0;
			p=realloc(key->owner,key->ownerSize);
			if (NULL==p) {

				return -1;
			}
			key->owner=p;
		} else {
			key->owner=malloc(key->ownerSize);
			if (!key->owner) {

				return -1;
			}
		}

		strcpy(key->owner,owner);
		key->flags |= KEY_FLAG_SYNC;
	} else if (key->owner) {
		free(key->owner);
		key->ownerSize=1;
		key->owner=0;
		key->flags |= KEY_FLAG_SYNC;
	}
	return key->ownerSize;
}

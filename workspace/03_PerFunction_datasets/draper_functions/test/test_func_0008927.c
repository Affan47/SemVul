find(const void* key, const void **keyp) const
{
    u_int index = (u_int)(hashKey(key) % buckets.length());
    const fxDictBucket* bucket = buckets[index];
    while (bucket && compareKeys(key,KEY(bucket))) bucket = bucket->next;
    if (bucket) {
	if (keyp != 0) *keyp = &KEY(bucket);
	return VALUE(bucket);
    } else {
	if (keyp != 0) *keyp = 0;
	return 0;
    }
}

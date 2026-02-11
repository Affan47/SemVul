DeleteKey(FCDAnimationKey* key)
{
	FCDAnimationKeyList::iterator kitr = keys.find(key);
	if (kitr == keys.end()) return false;

	keys.erase(kitr);
	delete key;
	return true;
}

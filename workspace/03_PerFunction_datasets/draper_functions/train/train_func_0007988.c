keyDecRef(Key *key)
{
	if (!key) return -1;

	if (key->ksReference>0) return -- key->ksReference;
	else return 0;
}

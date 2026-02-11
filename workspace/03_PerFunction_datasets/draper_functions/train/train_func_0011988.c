get_hash_4(int index)
{
	return string_hash(saved_key[index]) & 0xfffff;
}

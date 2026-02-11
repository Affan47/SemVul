octstr_hash_key(Octstr *ostr)
{
    unsigned long key = 0;
    long i;

    if (ostr == NULL)
	return 0;

    for (i = 0; i < octstr_len(ostr); i++)
	key = key + octstr_get_char(ostr, i);

    return key;
}

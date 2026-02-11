_kadm5_exists_keys(Key *keys1, int len1, Key *keys2, int len2)
{
    size_t i, j;
    size_t optimize;

    for (i = 0; i < len1; ++i) {
	optimize = 0;
	for (j = 0; j < len2; j++) {
	    if ((keys1[i].salt != NULL && keys2[j].salt == NULL)
		|| (keys1[i].salt == NULL && keys2[j].salt != NULL))
		continue;

	    if (keys1[i].salt != NULL) {
		if (keys1[i].salt->type != keys2[j].salt->type)
		    continue;
		if (keys1[i].salt->salt.length != keys2[j].salt->salt.length)
		    continue;
		if (memcmp (keys1[i].salt->salt.data, keys2[j].salt->salt.data,
			    keys1[i].salt->salt.length) != 0)
		    continue;
	    }
	    if (keys1[i].key.keytype != keys2[j].key.keytype)
		continue;
	    optimize = 1;
	    if (keys1[i].key.keyvalue.length != keys2[j].key.keyvalue.length)
		continue;
	    if (memcmp (keys1[i].key.keyvalue.data, keys2[j].key.keyvalue.data,
			keys1[i].key.keyvalue.length) != 0)
		continue;

	    return 1;
	}


	if (optimize)
	    return 0;
    }
    return 0;
}

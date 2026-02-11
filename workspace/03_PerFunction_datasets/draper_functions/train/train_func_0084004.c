store(key, data)
datum key;
datum data;
{
	of_t value;

	if (pagf == NULL) {
		DEBUG(("store: database not open!\n"));
		return(-1);
	} else if (basef == NULL) {
		basef = latebase();
		if (basef == NULL)
			return(-1);
	}
	if (pagronly) {
		DEBUG(("store: database open read-only\n"));
		return(-1);
	}
	if (data.dsize != SOF) {
		DEBUG(("store: value size wrong (%d)\n", data.dsize));
		return(-1);
	}
	if (key.dsize >= DBZMAXKEY) {
		DEBUG(("store: key size too big (%d)\n", key.dsize));
		return(-1);
	}


	(void) memcpy((POINTER)&value, (POINTER)data.dptr, SOF);
	if (value > conf.vused[0])
		conf.vused[0] = value;
	value >>= conf.dropbits;
	DEBUG(("store: (%s, %ld)\n", key.dptr, (long)value));
	if (!okayvalue(value)) {
		DEBUG(("store: reserved bit or overflow in 0x%lx\n", value));
		return(-1);
	}


	start(&srch, &key, prevp);
	while (search(&srch) != NOTFOUND)
		continue;

	prevp = FRESH;
	conf.used[0]++;
	DEBUG(("store: used count %ld\n", conf.used[0]));
	written = 1;
	return(set(&srch, value));
}

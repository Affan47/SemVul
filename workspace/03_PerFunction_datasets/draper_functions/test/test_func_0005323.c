writeWORD (int l) {
	if (!isok())
	    return false;
	if ((remainingchunklen >= 0) && (remainingchunklen < 2))
	    return false;

	unsigned char buf[4];
	buf [0] = l & 0xff;
	buf [1] = (l & 0xff00) >> 8;
	ofs.write ((char *)&buf[0], 2);
	if (!isok())
	    return false;
	if (remainingchunklen >= 0)
	    remainingchunklen -= 2;
	return true;
    }

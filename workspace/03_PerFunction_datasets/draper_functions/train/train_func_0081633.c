getLenString(int &length, const char *desc)
{
	byte b;
	mStream->readx(&b, 1);
	switch (b) {
    	case 0xfe: {
		byte neta[2];
		mStream->readx(&neta, 2);
		length = createHostInt(neta, 2, big_endian);
		break;
	}
	case 0xff: {
		byte neta[4];
		mStream->readx(&neta, 4);
		length = createHostInt(neta, 4, big_endian);
		break;
	}
	default:
		length = b;
		break;
	}
	if (length==0) return NULL;
	byte *p = ht_malloc(length);
	mStream->readx(p, length);
	return p;
}

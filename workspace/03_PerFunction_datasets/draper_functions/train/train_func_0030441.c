cgcef_hash(const unsigned char *name) {
    unsigned long hash = 0;
    unsigned long tmp;

    while (*name) {
	hash = (hash << 4) + (unsigned char)*name++;
	if ((tmp = hash & 0xf0000000)) {
	    hash ^= tmp | (tmp >> 24);
	}
    }
    return hash;
}

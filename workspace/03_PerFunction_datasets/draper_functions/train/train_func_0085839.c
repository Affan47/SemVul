len_oid (const heim_oid *oid)
{
    size_t ret = 1;
    size_t n;

    for (n = 2; n < oid->length; ++n) {
	unsigned u = oid->components[n];

	do {
	    ++ret;
	    u /= 128;
	} while(u > 0);
    }
    return ret;
}

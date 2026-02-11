hashKey(const void* key) const
{
    u_long u = 0;
    const u_long* p = (const u_long*)key;
    u_int l = keysize;
    while (l>=sizeof (u_long)) {
	u ^= *p++;
	l -= sizeof (u_long);
    }
    return u;
}

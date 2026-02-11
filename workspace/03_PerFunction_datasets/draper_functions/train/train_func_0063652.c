stringrel(STRING *s1, STRING *s2)
{
	char *c1, *c2;
	long i1, i2;

	if (s1 == s2)
		return 0;

	i1 = s1->s_len;
	i2 = s2->s_len;
	if (i2 == 0)
		return (i1 > 0);
	if (i1 == 0)
		return -1;
	c1 = s1->s_str;
	c2 = s2->s_str;
	while (i1 > 1 && i2 > 1 && *c1 == *c2) {
		i1--;
		i2--;
		c1++;
		c2++;
	}
	if ((unsigned char) *c1 > (unsigned char) *c2) return 1;
	if ((unsigned char) *c1 < (unsigned char) *c2) return -1;
	if (i1 < i2) return -1;
	return (i1 > i2);
}

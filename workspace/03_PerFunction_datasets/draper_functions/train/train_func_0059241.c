pHash2(Key key)
{
    float *point = (float *)(((HashElement2 *)key)->point);
    long l, k;
    int i;
    float j;

    l = 0;
    for (i = 0; i < 2; i++)
    {
	j = primes[i] * point[i];
	k = *(int *)&j;
	k = (((k ^ (k >> 8))) ^ (k >> 16)) ^ (k >> 24);

	l += k;
    }

    return (PseudoKey)l;
}

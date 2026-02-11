FcCharSetIntersectLeaf (FcCharLeaf *result,
			const FcCharLeaf *al,
			const FcCharLeaf *bl)
{
    int	    i;
    FcBool  nonempty = FcFalse;

    for (i = 0; i < 256/32; i++)
	if ((result->map[i] = al->map[i] & bl->map[i]))
	    nonempty = FcTrue;
    return nonempty;
}

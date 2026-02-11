_FcStrSetAppend (FcStrSet *set, FcChar8 *s)
{
    if (FcStrSetMember (set, s))
    {
	FcStrFree (s);
	return FcTrue;
    }
    if (set->num == set->size)
    {
	FcChar8	**strs = malloc ((set->size + 2) * sizeof (FcChar8 *));

	if (!strs)
	    return FcFalse;
	if (set->num)
	    memcpy (strs, set->strs, set->num * sizeof (FcChar8 *));
	if (set->strs)
	    free (set->strs);
	set->size = set->size + 1;
	set->strs = strs;
    }
    set->strs[set->num++] = s;
    set->strs[set->num] = 0;
    return FcTrue;
}

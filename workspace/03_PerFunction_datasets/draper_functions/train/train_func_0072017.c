isSame(const SoFieldContainer *c1,
		    const SoFieldContainer *c2) const


{
    int	i;

    for (i = 0; i < fields.getLength(); i++)
	if (! getField(c1, i)->isSame(*getField(c2, i)))
	    return FALSE;

    return TRUE;
}

device_property_equal(
	gconstpointer v1,
	gconstpointer v2)
{
    const char *s1 = v1, *s2 = v2;

    while (*s1 && *s2) {
	if (toupper_and_underscore(*s1) != toupper_and_underscore(*s2))
	    return FALSE;
	s1++, s2++;
    }
    if (*s1 || *s2)
	return FALSE;

    return TRUE;
}

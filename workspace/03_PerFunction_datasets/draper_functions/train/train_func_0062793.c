vim_is_fastterm(name)
    char_u  *name;
{
    if (name == NULL)
	return FALSE;
    if (vim_is_xterm(name) || vim_is_vt300(name) || vim_is_iris(name))
	return TRUE;
    return (   STRNICMP(name, "hpterm", 6) == 0
	    || STRNICMP(name, "sun-cmd", 7) == 0
	    || STRNICMP(name, "screen", 6) == 0
	    || STRNICMP(name, "dtterm", 6) == 0);
}

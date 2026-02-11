vim_strsave_escape_csi(p)
    char_u *p;
{
    char_u	*res;
    char_u	*s, *d;


    res = alloc((unsigned)(STRLEN(p) * 3) + 1);
    if (res != NULL)
    {
	d = res;
	for (s = p; *s != NUL; )
	{
	    if (s[0] == K_SPECIAL && s[1] != NUL && s[2] != NUL)
	    {

		*d++ = *s++;
		*d++ = *s++;
		*d++ = *s++;
	    }
	    else
	    {


		d = add_char2buf(PTR2CHAR(s), d);
		mb_ptr_adv(s);
	    }
	}
	*d = NUL;
    }
    return res;
}

add_to_showcmd(c)
    int		c;
{
    char_u	*p;
    int		old_len;
    int		extra_len;
    int		overflow;
#if defined(FEAT_MOUSE)
    int		i;
    static int	ignore[] =
    {
# ifdef FEAT_GUI
	K_VER_SCROLLBAR, K_HOR_SCROLLBAR,
	K_LEFTMOUSE_NM, K_LEFTRELEASE_NM,
# endif
	K_IGNORE,
	K_LEFTMOUSE, K_LEFTDRAG, K_LEFTRELEASE,
	K_MIDDLEMOUSE, K_MIDDLEDRAG, K_MIDDLERELEASE,
	K_RIGHTMOUSE, K_RIGHTDRAG, K_RIGHTRELEASE,
	K_MOUSEDOWN, K_MOUSEUP,
	K_X1MOUSE, K_X1DRAG, K_X1RELEASE, K_X2MOUSE, K_X2DRAG, K_X2RELEASE,
	K_CURSORHOLD,
	0
    };
#endif

    if (!p_sc || msg_silent != 0)
	return FALSE;

    if (showcmd_visual)
    {
	showcmd_buf[0] = NUL;
	showcmd_visual = FALSE;
    }

#if defined(FEAT_MOUSE)

    if (IS_SPECIAL(c))
	for (i = 0; ignore[i] != 0; ++i)
	    if (ignore[i] == c)
		return FALSE;
#endif

    p = transchar(c);
    old_len = (int)STRLEN(showcmd_buf);
    extra_len = (int)STRLEN(p);
    overflow = old_len + extra_len - SHOWCMD_COLS;
    if (overflow > 0)
	mch_memmove(showcmd_buf, showcmd_buf + overflow,
						      old_len - overflow + 1);
    STRCAT(showcmd_buf, p);

    if (char_avail())
	return FALSE;

    display_showcmd();

    return TRUE;
}

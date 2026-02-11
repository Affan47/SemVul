ins_char_typebuf(c)
    int	    c;
{
#ifdef FEAT_MBYTE
    char_u	buf[MB_MAXBYTES];
#else
    char_u	buf[4];
#endif
    if (IS_SPECIAL(c))
    {
	buf[0] = K_SPECIAL;
	buf[1] = K_SECOND(c);
	buf[2] = K_THIRD(c);
	buf[3] = NUL;
    }
    else
    {
#ifdef FEAT_MBYTE
	buf[(*mb_char2bytes)(c, buf)] = NUL;
#else
	buf[0] = c;
	buf[1] = NUL;
#endif
    }
    (void)ins_typebuf(buf, KeyNoremap, 0, !KeyTyped, cmd_silent);
}

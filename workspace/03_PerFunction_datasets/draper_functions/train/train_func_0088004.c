ggets(str)
  char *str;
{
    char *s = str;
    int c;

    do {
        c = ggetchar();
        if (c == '\b' ) {
            if (s != str) {
                gputchar('\b');
                gputchar((int)' ');
                gputchar('\b');
                s--;
            } else {
#ifdef AMIGA
                gputchar((int)0x9b);
                gputchar((int)0x43);
#else

#endif
                gputchar((int)0x07);
            }
        } else *s++ = (char) c;
    } while (c != (int) '\n' && !abort_flag);

    *(s-1) = EOS;
    if (abort_flag) *str = EOS;
    return str;
}

fl_skipws(value_t *args, u_int32_t nargs)
{
    argcount("skip-ws", nargs, 2);
    ios_t *s = fl_toiostream(args[0], "skip-ws");
    int newlines = (args[1]!=FL_F);
    uint32_t wc=0;
    if (ios_peekutf8(s, &wc) == IOS_EOF)
        return FL_EOF;
    value_t skipped = FL_F;
    while (!ios_eof(s) && is_uws(wc) && (newlines || wc!=10)) {
        skipped = FL_T;
        ios_getutf8(s, &wc);
        ios_peekutf8(s, &wc);
    }
    return skipped;
}

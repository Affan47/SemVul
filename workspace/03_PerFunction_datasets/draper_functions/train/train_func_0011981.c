put_seq(
    char *  begin,
    char *  seq
)


{
    FILEINFO *  file = infile;
    int     c;

    cerror( "Operand of _Pragma() is not a string literal"
            , NULL, 0L, NULL);
    while (c = get_ch(), file == infile)
        *seq++ = c;
    unget_ch();
    out_ptr = seq;
    putout( begin);
}

DumpBoard(FILE * fp)
{
    ASSERT(fp != NULL);
    squareT s;
    for(int i = 7; i >= 0; i--)
    {
        fputs("   ", fp);
        for(int j = 0; j < 8; ++j)
        {
            s = (i * 8) + j;
            putc(PIECE_CHAR[Board[s]], fp);
            putc(' ', fp);
        }
        putc('\n', fp);
    }
}

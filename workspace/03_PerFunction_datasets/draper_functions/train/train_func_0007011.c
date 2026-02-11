treeFlushLen ()
{
    int  ch;

    if ((ch = treeGetCh()) == ':')
        (void) processLength();
    else if (ch != EOF)
        (void) ungetc(ch, INFILE);

}

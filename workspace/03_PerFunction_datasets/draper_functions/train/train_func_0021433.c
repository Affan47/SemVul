W_PrintDirectory(void)
{
    unsigned int i, n;


    for (i=0; i<numlumps; ++i)
    {
        for (n=0; n<8 && lumpinfo[i].name[n] != '\0'; ++n)
            putchar(lumpinfo[i].name[n]);
        putchar('\n');
    }
}

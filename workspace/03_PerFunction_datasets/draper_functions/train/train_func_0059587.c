rmd160_mixblock( RMD160_CONTEXT *hd, char *buffer )
{
    char *p = buffer;
    transform( hd, buffer );
#define X(a) do { *(u32*)p = hd->h##a ; p += 4; } while(0)
    X(0);
    X(1);
    X(2);
    X(3);
    X(4);
#undef X
}

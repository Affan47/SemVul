supbif(supcxdef *sup, void (*bif[])(bifcxdef*, int), int bifsiz)
{
    supbidef *p;
    int       i;

    for (p = supbitab, i = 0 ; p->supbinam ; ++i, ++p)
    {
        if (i >= bifsiz) errsig(sup->supcxerr, ERR_MANYBIF);
        bif[i] = p->supbifn;
    }
}

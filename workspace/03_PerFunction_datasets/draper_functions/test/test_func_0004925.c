vg_verifygrpdep( char* name1, char* name2 )
{
    HFILEID f1;
    HFILEID f2;
    int32   nlnk1;
    int32   nlnk2;


    if ((f1 = Hopen(name1, DFACC_READ, 0)) == FAIL)
    {
        printf("\nFile (%s) failed to open.\n", name1);
        return -1;
    }
    if ((f2 = Hopen(name2, DFACC_READ, 0)) == FAIL)
    {
        printf("\nFile (%s) failed to open.\n", name2);
        return -1;
    }

    nlnk1 = vg_getngrpdep( f1 );
    nlnk2 = vg_getngrpdep( f2 );

    Hclose(f1);
    Hclose(f2);

    return (nlnk1 == nlnk2) ? 0: 1;

}

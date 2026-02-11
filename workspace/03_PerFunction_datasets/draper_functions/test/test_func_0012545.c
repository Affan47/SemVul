ajPdbDel(AjPPdb *Ppdb)
{
    ajuint i = 0U;

    AjPAtom atom = NULL;

    AjPPdb pdb = NULL;

    if (!Ppdb || !*Ppdb)
        return;

    pdb = *Ppdb;

    ajStrDel(&pdb->Pdb);
    ajStrDel(&pdb->Compnd);
    ajStrDel(&pdb->Source);

    ajChararrDel(&pdb->gpid);

    while (ajListPop(pdb->Water, (void **) &atom))
        ajAtomDel(&atom);

    ajListFree(&pdb->Water);

    while (ajListPop(pdb->Groups, (void **) &atom))
        ajAtomDel(&atom);

    ajListFree(&pdb->Groups);

    for (i = 0U; i < pdb->Nchn; i++)
        ajChainDel(&pdb->Chains[i]);

    AJFREE(pdb->Chains);

    AJFREE(pdb);

    *Ppdb = NULL;

    return;
}

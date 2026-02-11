ensGvgenotypeTrace(const EnsPGvgenotype gvg, ajuint level)
{
    AjIList iter = NULL;

    AjPStr allele = NULL;
    AjPStr indent = NULL;

    if (!gvg)
        return ajFalse;

    indent = ajStrNew();

    ajStrAppendCountK(&indent, ' ', level * 2);

    ajDebug("%SensGvgenotypeTrace %p\n"
            "%S  Use %u\n"
            "%S  Identifier %u\n"
            "%S  Adaptor %p\n"
            "%S  Gvvariation %p\n"
            "%S  Alleles %p\n"
            "%S  Subhandle '%S'\n"
            "%S  Subidentifier %u\n",
            indent, gvg,
            indent, gvg->Use,
            indent, gvg->Identifier,
            indent, gvg->Adaptor,
            indent, gvg->Gvvariation,
            indent, gvg->Alleles,
            indent, gvg->Subhandle,
            indent, gvg->Subidentifier);

    ensGvvariationTrace(gvg->Gvvariation, level + 1);

    iter = ajListIterNew(gvg->Alleles);

    while (!ajListIterDone(iter))
    {
        allele = ajListstrIterGet(iter);

        ajDebug("%S    Allele '%S'\n", indent, allele);
    }

    ajListIterDel(&iter);

    ajStrDel(&indent);

    return ajTrue;
}

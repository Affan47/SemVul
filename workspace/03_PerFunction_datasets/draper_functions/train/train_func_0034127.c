TextPrintComment(FILE * pf, const moverecord * pmr)
{

    char *sz = pmr->sz;


    if (sz) {

        fputs(_("Annotation:\n"), pf);
        fputs(sz, pf);
        fputs("\n", pf);

    }


}

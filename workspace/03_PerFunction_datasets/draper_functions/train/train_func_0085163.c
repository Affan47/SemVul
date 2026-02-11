LoadCollection(char *sz)
{

    listOLD *plCollection, *pl, *plRoot, *plProp;
    FILE *pf;
    int fBackgammon;
    property *pp;

    fError = FALSE;
    SGFErrorHandler = ErrorHandler;

    if (strcmp(sz, "-")) {
        if (!(pf = g_fopen(sz, "r"))) {
            outputerr(sz);
            return NULL;
        }
        szFile = sz;
    } else {

        pf = stdin;
        szFile = "(stdin)";
    }

    plCollection = SGFParse(pf);

    if (pf != stdin)
        fclose(pf);


    if (plCollection) {
        pl = plCollection->plNext;
        while (pl != plCollection) {
            plRoot = ((listOLD *) ((listOLD *) pl->p)->plNext->p)->plNext->p;
            fBackgammon = FALSE;
            for (plProp = plRoot->plNext; plProp != plRoot; plProp = plProp->plNext) {
                pp = plProp->p;

                if (pp->ach[0] == 'G' && pp->ach[1] == 'M' && pp->pl->plNext->p && atoi((char *)
                                                                                        pp->pl->plNext->p) == 6) {
                    fBackgammon = TRUE;
                    break;
                }
            }

            pl = pl->plNext;

            if (!fBackgammon) {
                FreeList(pl->plPrev->p, 1);
                ListDelete(pl->plPrev);
            }
        }

        if (ListEmpty(plCollection)) {
            ErrorHandler(_("warning: no backgammon games in SGF file"), TRUE);
            free(plCollection);
            plCollection = NULL;
        }
    }

    return plCollection;
}

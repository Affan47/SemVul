coalesce(rlist,lines,psize)


struct s_rlist **rlist;
int lines, psize;
{
    int i;
    struct s_rlist *listL, *listU, *listp;

    for (i = 1; i < lines; i++) {

        for (listL = rlist[i]; listL; listL = listL->next) {
            listp = NULL;
            for (listU = rlist[i-1]; listU;
                    listp = listU, listU = listU->next) {
                if (listL->xl == listU->xl && listL->xr == listU->xr) {
                    listL->yu = listU->yu;
                    if (listp == NULL) {
                        rlist[i-1] = listU->next;
                    }
                    else {
                        listp->next = listU->next;
                    }
                    free(listU);
                    break;
                }
            }
        }
    }
}

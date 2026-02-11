search_const_dcomplex(double re, double im)
{
    Const_table *cpt;
    Boolean     found = FALSE;

    cpt = const_head;
    while((found == FALSE)&&(cpt != NULL)) {
        if (  (cpt->type == TYPE_DCOMPLEX)
            &&(cpt->val.dc.re == re)
            &&(cpt->val.dc.im == im))
            found = TRUE;
        else
            cpt = cpt->next;
    }

    return cpt;
}

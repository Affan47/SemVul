qfits_header_sort(qfits_header ** hdr)
{
    qfits_header    *   sorted;
    keytuple        *   k;
    keytuple        *   kbf;
    keytuple        *   next;
    keytuple        *   last;


    if (hdr == NULL) return -1;
    if (*hdr == NULL) return -1;
    if ((*hdr)->n < 2) return 0;


    sorted = qfits_header_new();


    k = (keytuple*)(*hdr)->first;
    next = k->next;
    sorted->first = sorted->last = k;
    k->next = k->prev = NULL;
    sorted->n = 1;


    while (next != NULL) {
        k = next;
        next = k->next;


        kbf = (keytuple*)sorted->first;
        while (kbf!=NULL) {
            if (k->typ < kbf->typ) break;
            kbf = kbf->next;
        }


        if (kbf == NULL) {

            last = sorted->last;
            sorted->last = k;
            k->next = NULL;
            k->prev = last;
            last->next = k;
        } else {

            k->next = kbf;
            k->prev = kbf->prev;
            if (kbf->prev != NULL) (kbf->prev)->next = k;
            else sorted->first = k;
            kbf->prev = k;
        }
        (sorted->n) ++;
    }


    (*hdr)->first = (*hdr)->last = NULL;
    qfits_header_destroy(*hdr);
    *hdr = sorted;

    return 0;
}

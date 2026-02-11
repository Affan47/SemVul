pvl_push(pvl_list l,void *d)
{
    struct pvl_list_t *L = (struct pvl_list_t *)l;
    struct pvl_elem_t *E = pvl_new_element(d,0,L->tail);


    if (L->tail != 0)
    {
	L->tail->next = E;
    }

    if (L->head == 0)
    {
	L->head = E;
    }

    L->tail = E;

    L->count++;

}

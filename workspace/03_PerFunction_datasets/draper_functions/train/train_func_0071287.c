pvl_find(pvl_list l,pvl_findf f,void* v)
{
    pvl_elem e;

    for (e=pvl_head(l); e!= 0; e = pvl_next(e))
    {
	if ( (*f)(((struct pvl_elem_t *)e)->d,v) == 1)
	{

	    ((struct pvl_list_t *)l)->p = e;
	    return e;
	}
    }

    return 0;

}

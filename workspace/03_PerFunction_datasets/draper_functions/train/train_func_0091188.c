SuiteSparse_realloc

(
    size_t nitems_new,
    size_t nitems_old,
    size_t size_of_item,
    void *p,
    int *ok
)
{
    size_t size ;
    if (nitems_old < 1) nitems_old = 1 ;
    if (nitems_new < 1) nitems_new = 1 ;
    if (size_of_item < 1) size_of_item = 1 ;
    size = nitems_new * size_of_item  ;

    if (size != ((double) nitems_new) * size_of_item)
    {

        (*ok) = 0 ;
    }
    else if (p == NULL)
    {

        p = SuiteSparse_malloc (nitems_new, size_of_item) ;
        (*ok) = (p != NULL) ;
    }
    else if (nitems_old == nitems_new)
    {

        (*ok) = 1 ;
    }
    else
    {

        void *pnew ;
        pnew = (void *) (SuiteSparse_config.realloc_func) (p, size) ;
        if (pnew == NULL)
        {
            if (nitems_new < nitems_old)
            {


                (*ok) = 1 ;
            }
            else
            {

                (*ok) = 0 ;
            }
        }
        else
        {

            p = pnew ;
            (*ok) = 1 ;
        }
    }
    return (p) ;
}

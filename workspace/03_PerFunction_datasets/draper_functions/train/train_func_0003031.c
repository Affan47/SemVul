SuiteSparse_calloc
(
    size_t nitems,
    size_t size_of_item
)
{
    void *p ;
    size_t size ;
    if (nitems < 1) nitems = 1 ;
    if (size_of_item < 1) size_of_item = 1 ;
    size = nitems * size_of_item  ;

    if (size != ((double) nitems) * size_of_item)
    {

        p = NULL ;
    }
    else
    {
        p = (void *) (SuiteSparse_config.calloc_func) (nitems, size_of_item) ;
    }
    return (p) ;
}

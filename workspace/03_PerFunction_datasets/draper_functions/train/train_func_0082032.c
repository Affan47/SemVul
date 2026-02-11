var_free()
{
    VARIABLE *ptr;

    for( ptr = (VARIABLE *)VAR_HEAD; ptr; ptr = NEXT(ptr) )
    {
        if ( --REFCNT(ptr) == 0 )
        {
            FREEMEM((char *)MATR(ptr));
            FREEMEM((char *)ptr->this);
        }
     }

     lst_purge(VARIABLES);

     return;
}

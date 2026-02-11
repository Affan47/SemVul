inverse_permutation
(
    Int *P,
    Int *Pinv,
    Int n
)
{
    Int i, k ;
    for (i = 0 ; i < n ; i++)
    {
        Pinv [i] = EMPTY ;
    }
    for (k = 0 ; k < n ; k++)
    {
        i = P [k] ;
        if (i < 0 || i >= n || Pinv [i] != EMPTY)
        {

            return (FALSE) ;
        }
        Pinv [i] = k ;
    }
    return (TRUE) ;
}

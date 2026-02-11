Set_subset(wordptr X, wordptr Y)
{
    N_word size = BV_SIZE_(X);
    boolean r = false;

    if ((size > 0) and (BV_BITS_(X) == BV_BITS_(Y)))
    {
        r = true;
        while (r and (size-- > 0)) r = ((*X++ AND NOT *Y++) == 0);
    }
    return(r);
}

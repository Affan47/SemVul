BitVector_equal(wordptr X, wordptr Y)
{
    N_word  size = BV_SIZE_(X);
    N_word  mask = BV_MASK_(X);
    boolean r = false;

    if (BV_BITS_(X) == BV_BITS_(Y))
    {
        r = true;
        if (size > 0)
        {
            *(X+size-1) &= mask;
            *(Y+size-1) &= mask;
            while (r and (size-- > 0)) r = (*X++ == *Y++);
        }
    }
    return(r);
}

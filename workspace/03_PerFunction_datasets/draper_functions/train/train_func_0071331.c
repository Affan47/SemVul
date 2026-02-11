containsZero() const
{
    return (imin.negative && !imax.negative)
        || (!imin.negative && imin.value == 0);
}

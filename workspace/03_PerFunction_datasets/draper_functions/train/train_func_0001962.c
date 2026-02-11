add(le_int32 limit)
{
    if (fClientArrays) {
        return -1;
    }

    le_int32  index  = ensureCapacity();
    le_int32 *limits = (le_int32 *) fLimits;

    limits[index] = limit;

    return index;
}

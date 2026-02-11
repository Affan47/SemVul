function1d_search_value(
    pixelvalue    *    x,
    int             len,
    pixelvalue         key,
    int         *    foundPtr
)
{
    int    high,
        low,
        middle;

    low  = 0;
    high = len - 1;

    while (high >= low) {
        middle = (high + low) / 2;
        if (key > x[middle]) {
            low = middle + 1;
        } else if (key < x[middle]) {
            high = middle - 1;
        } else {
            *foundPtr = 1;
            return (middle);
        }
    }
    *foundPtr = 0;
    return (low);
}

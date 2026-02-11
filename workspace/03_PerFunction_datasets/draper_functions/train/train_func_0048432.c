qcksrt(short array[], int l, int h)
{
    int lower,
        upper,
        top,
        i,
        j,
        pivot,
        lostack[14],
        histack[14];

    top = 1;
    lostack[top] = l;
    histack[top] = h;
    while (top != 0)
    {
        lower = lostack[top];
        upper = histack[top--];

        while (upper > lower)
        {
            i = lower;
            pivot = array[lower];
            for (j = lower + 1; j <= upper; j++)
            {
                if (array[j] < pivot)
                {
                    array[i] = array[j];
                    i++;
                    array[j] = array[i];
                }
            }
            array[i] = pivot;

            top++;
            if (i - lower < upper - i)
            {
                lostack[top] = i + 1;
                histack[top] = upper;
                upper = i - 1;
            }
            else
            {
                histack[top] = i - 1;
                lostack[top] = lower;
                lower = i + 1;
            }
        }
    }

    return;
}

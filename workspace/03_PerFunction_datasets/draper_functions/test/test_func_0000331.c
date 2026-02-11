binary_search( WCHAR ch, int low, int high )
{
    extern const WCHAR unicode_compose_table[];
    while (low <= high)
    {
        int pos = (low + high) / 2;
        if (unicode_compose_table[2*pos] < ch)
        {
            low = pos + 1;
            continue;
        }
        if (unicode_compose_table[2*pos] > ch)
        {
            high = pos - 1;
            continue;
        }
        return pos;
    }
    return -1;
}

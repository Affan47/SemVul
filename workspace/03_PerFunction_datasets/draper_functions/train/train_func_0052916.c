pma_bin_search(struct leaf *region, int min_i, int max_i, int value,
                    int *ins_pt)
{
    int mid;
    int l, r;

    mid = (min_i + max_i)/2;

    while (min_i < max_i)
    {

        l = r = mid;
        while (empty(region, l) &&
               empty(region, r) &&
               (l > min_i || r < max_i))
        {
            if (l > min_i) l--;
            if (r < max_i) r++;
        }

        if (!empty(region, l))
            mid = l;
        else if (!empty(region, r))
            mid = r;
        else
            break;

        if (region[mid].key < value)
            min_i = mid + 1;
        else if (region[mid].key > value)
            max_i = mid - 1;
        else
            break;

        mid = (min_i + max_i)/2;
    }
    *ins_pt = mid;
    return region[mid].key == value;
}

move_sort_moves(int *movebuf, int count)
{
    int *move, *end, tmp, swapped;

    end = movebuf + count - 1;

    do
    {
        swapped = 0;
        for (move = movebuf; move < end; ++move)
        {
            if (search.history[*move & 0x7fff] < search.history[*(move + 1) & 0x7fff])
            {
                tmp = *move;
                *move = *(move + 1);
                *(move + 1) = tmp;
                swapped = 1;
            }
        }
    } while (swapped);
}

GC_number_stack_black_listed(struct hblk *start,
                                         struct hblk *endp1)
{
    register struct hblk * h;
    word result = 0;

    for (h = start; h < endp1; h++) {
        word index = PHT_HASH((word)h);

        if (get_pht_entry_from_index(GC_old_stack_bl, index)) result++;
    }
    return(result);
}

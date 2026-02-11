sort_candidate_data_by_bubble_sort(int candidate[],
                   int cand_num,
                   Block *target_mt,
                   int (*comp_func)(int cand_i,
                            int cand_j,
                            Block *target_mt))
{
    int sort_count;
    int i;

    do {
        sort_count = 0;

        for (i = 0; i < cand_num - 1; i++) {
            if ((*comp_func)(candidate[i],
                     candidate[i + 1],
                     target_mt) < 0) {
                candidate_swap_by_dt(&(candidate[i]),
                             &(candidate[i + 1]));
                sort_count++;
            }
        }

    } while (sort_count != 0);
}

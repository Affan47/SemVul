compute_left_or_right(GtBittab **left_or_right,
                                  const ConsensusSA *csa,
                                  bool (*cmp_func) (const ConsensusSA *csa,
                                                    unsigned long sa_1,
                                                    unsigned long sa_2))
{
  unsigned long sa, sa_1;
  gt_assert(csa && left_or_right && *left_or_right);
  for (sa = 0; sa < csa->number_of_sas; sa++) {
    for (sa_1 = 0; sa_1 < csa->number_of_sas; sa_1++) {
      if (cmp_func(csa, sa, sa_1) && compatible(csa, sa, sa_1))
        gt_bittab_set_bit(left_or_right[sa], sa_1);
    }
  }
}

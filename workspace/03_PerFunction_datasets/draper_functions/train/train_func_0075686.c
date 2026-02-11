set_of_sas_is_sorted(const void *set_of_sas,
                                 unsigned long number_of_sas,
                                 size_t size_of_sa, GetGenomicRangeFunc
                                 get_genomic_range)
{
  GtRange gt_range_a, gt_range_b;
  unsigned long max_end;
  const char *sa;

  gt_assert(set_of_sas && number_of_sas && size_of_sa && get_genomic_range);


  gt_range_a = get_genomic_range(set_of_sas);
  max_end = gt_range_a.end;


  for (sa = (char*) set_of_sas + size_of_sa;
       sa < (char*) set_of_sas + number_of_sas * size_of_sa;
       sa = sa + size_of_sa) {

    gt_range_b = get_genomic_range(sa);


    if (!(gt_range_a.start <= gt_range_b.start)) return false;


    gt_range_a = gt_range_b;
    if (gt_range_a.end > max_end)
      max_end = gt_range_a.end;
  }
  return true;
}

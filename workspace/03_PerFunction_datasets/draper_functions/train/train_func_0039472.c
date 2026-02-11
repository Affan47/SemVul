insn_to_prefetch_ratio_too_small_p (unsigned ninsns, unsigned prefetch_count,
                                     unsigned unroll_factor)
{
  int insn_to_prefetch_ratio;


  insn_to_prefetch_ratio = (unroll_factor * ninsns) / prefetch_count;
  if (insn_to_prefetch_ratio < MIN_INSN_TO_PREFETCH_RATIO)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
        fprintf (dump_file,
		 "Not prefetching -- instruction to prefetch ratio (%d) too small\n",
		 insn_to_prefetch_ratio);
      return true;
    }

  return false;
}

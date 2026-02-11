init_hints(Uniftype utype,
		int bsub_wt_attr,
		BOOL collect_labels,
		BOOL back_demod_hints,
		void (*demod_proc) (Topform, int, int, BOOL, BOOL))
{
  Bsub_wt_attr = bsub_wt_attr;
  Collect_labels = collect_labels;
  Back_demod_hints = back_demod_hints;
  Demod_proc = demod_proc;
  Hints_idx = lindex_init(FPA, utype, 10, FPA, utype, 10);
  if (Back_demod_hints)
    Back_demod_idx = mindex_init(FPA, utype, 10);
  Redundant_hints = clist_init("redundant_hints");
}

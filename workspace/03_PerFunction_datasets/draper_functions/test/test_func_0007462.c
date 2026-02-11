TopSort(MutableFstClass *fst) {
  TopSortArgs args(fst);

  Apply<Operation<TopSortArgs> >("TopSort", fst->ArcType(), &args);

  return args.retval;
}

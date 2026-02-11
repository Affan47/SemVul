merge_lists(struct predlist lists[], int nlists,
	    struct predlist *name_list,
	    struct predlist *regex_list,
	    struct predicate **last)
{
  int i;
  static void (*mergefn)(struct predlist *, struct predicate**);

  mergefn = predlist_merge_sort;

  mergefn(name_list,   last);
  mergefn(regex_list,  last);

  for (i=0; i<nlists; i++)
    mergefn(&lists[i], last);
}

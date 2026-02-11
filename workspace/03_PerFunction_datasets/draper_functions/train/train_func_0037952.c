make_quick(PARAM *param,
                                            bool retrieve_full_rows,
                                            MEM_ROOT *parent_alloc)
{
  QUICK_INDEX_MERGE_SELECT *quick_imerge;
  QUICK_RANGE_SELECT *quick;

  if (!(quick_imerge= new QUICK_INDEX_MERGE_SELECT(param->thd, param->table)))
    return NULL;

  quick_imerge->records= records;
  quick_imerge->read_time= read_cost;
  for (TRP_RANGE **range_scan= range_scans; range_scan != range_scans_end;
       range_scan++)
  {
    if (!(quick= (QUICK_RANGE_SELECT*)
          ((*range_scan)->make_quick(param, FALSE, &quick_imerge->alloc)))||
        quick_imerge->push_quick_back(quick))
    {
      delete quick;
      delete quick_imerge;
      return NULL;
    }
  }
  return quick_imerge;
}

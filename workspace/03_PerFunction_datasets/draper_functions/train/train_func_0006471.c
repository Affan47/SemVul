icaldirset_get_current_component(icalset* set)
{
  icaldirset *dset = (icaldirset*)set;

  if (dset->cluster == 0){
    icaldirset_get_first_component(set);
    }
  if(dset->cluster == 0){
	return 0;
    }

  return icalcluster_get_current_component(dset->cluster);
}

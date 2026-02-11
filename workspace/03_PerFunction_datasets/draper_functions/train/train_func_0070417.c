duplicate_eh_regions (struct function *ifun,
		      eh_region copy_region, int outer_lp,
		      duplicate_eh_regions_map map, void *map_data)
{
  struct duplicate_eh_regions_data data;
  eh_region outer_region;

#ifdef ENABLE_CHECKING
  verify_eh_tree (ifun);
#endif

  data.label_map = map;
  data.label_map_data = map_data;
  data.eh_map = pointer_map_create ();

  outer_region = get_eh_region_from_lp_number (outer_lp);


  if (copy_region)
    duplicate_eh_regions_1 (&data, copy_region, outer_region);
  else
    {
      eh_region r;
      for (r = ifun->eh->region_tree; r ; r = r->next_peer)
	duplicate_eh_regions_1 (&data, r, outer_region);
    }

#ifdef ENABLE_CHECKING
  verify_eh_tree (cfun);
#endif

  return data.eh_map;
}

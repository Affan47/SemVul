hwloc_level_take_objects(hwloc_obj_t top_obj,
			 hwloc_obj_t *current_objs, unsigned n_current_objs,
			 hwloc_obj_t *taken_objs, unsigned n_taken_objs __hwloc_attribute_unused,
			 hwloc_obj_t *remaining_objs, unsigned n_remaining_objs __hwloc_attribute_unused)
{
  unsigned taken_i = 0;
  unsigned new_i = 0;
  unsigned i, j;

  for (i = 0; i < n_current_objs; i++)
    if (hwloc_type_cmp(top_obj, current_objs[i]) == HWLOC_TYPE_EQUAL) {

      taken_objs[taken_i++] = current_objs[i];
      for (j = 0; j < current_objs[i]->arity; j++)
	remaining_objs[new_i++] = current_objs[i]->children[j];
    } else {

      remaining_objs[new_i++] = current_objs[i];
    }

#ifdef HWLOC_DEBUG

  assert(taken_i == n_taken_objs);
  assert(new_i == n_current_objs - n_taken_objs + n_remaining_objs);
#endif

  return new_i;
}

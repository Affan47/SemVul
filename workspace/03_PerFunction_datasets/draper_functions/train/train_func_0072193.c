hwloc_calc_output(hwloc_topology_t topology, const char *sep, hwloc_bitmap_t set)
{
  if (singlify)
    hwloc_bitmap_singlify(set);

  if (showobjs) {
    hwloc_bitmap_t remaining = hwloc_bitmap_dup(set);
    int first = 1;
    if (!sep)
      sep = " ";
    while (!hwloc_bitmap_iszero(remaining)) {
      char type[64];
      unsigned idx;
      hwloc_obj_t obj = hwloc_get_first_largest_obj_inside_cpuset(topology, remaining);
      if (!obj) {
        hwloc_bitmap_free(remaining);
        fprintf(stderr, "No object included in this cpuset\n");
        return EXIT_FAILURE;
      }
      hwloc_obj_type_snprintf(type, sizeof(type), obj, 1);
      idx = logicalo ? obj->logical_index : obj->os_index;
      if (idx == (unsigned) -1)
        printf("%s%s", first ? (const char *) "" : sep, type);
      else
        printf("%s%s:%u", first ? (const char *) "" : sep, type, idx);
      hwloc_bitmap_andnot(remaining, remaining, obj->cpuset);
      first = 0;
    }
    printf("\n");
    hwloc_bitmap_free(remaining);
  } else if (numberofdepth != -1) {
    unsigned nb = 0;
    hwloc_obj_t obj = NULL;
    while ((obj = hwloc_get_next_obj_covering_cpuset_by_depth(topology, set, numberofdepth, obj)) != NULL)
      nb++;
    printf("%u\n", nb);
  } else if (intersectdepth != -1) {
    hwloc_obj_t proc, prev = NULL;
    if (!sep)
      sep = ",";
    while ((proc = hwloc_get_next_obj_covering_cpuset_by_depth(topology, set, intersectdepth, prev)) != NULL) {
      if (prev)
	printf("%s", sep);
      printf("%u", logicalo ? proc->logical_index : proc->os_index);
      prev = proc;
    }
    printf("\n");
  } else if (hiernblevels) {
    if (!sep)
      sep = " ";
    hwloc_calc_hierarch_output(topology, "", sep, hwloc_get_root_obj(topology), set, 0);
    printf("\n");
  } else {
    char *string = NULL;
    if (taskset)
      hwloc_bitmap_taskset_asprintf(&string, set);
    else
      hwloc_bitmap_asprintf(&string, set);
    printf("%s\n", string);
    free(string);
  }
  return EXIT_SUCCESS;
}

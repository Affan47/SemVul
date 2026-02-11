insert_task(hwloc_topology_t topology, hwloc_cpuset_t cpuset, const char * name)
{
  hwloc_obj_t obj;

  hwloc_bitmap_and(cpuset, cpuset, hwloc_topology_get_topology_cpuset(topology));
  if (hwloc_bitmap_iszero(cpuset))
    return NULL;


  obj = hwloc_topology_insert_misc_object_by_cpuset(topology, cpuset, name);
  if (!obj) {

    char *s;
    hwloc_bitmap_asprintf(&s, cpuset);
    obj = hwloc_get_obj_covering_cpuset(topology, cpuset);
    if (obj) {
      obj = hwloc_topology_insert_misc_object_by_parent(topology, obj, name);
      fprintf(stderr, "Inserted process `%s' below parent larger than cpuset %s\n", name, s);
    } else {
      fprintf(stderr, "Failed to insert process `%s' with cpuset %s\n", name, s);
    }
    free(s);
  }

  return obj;
}

hwloc_look_noos(struct hwloc_backend *backend)
{
  struct hwloc_topology *topology = backend->topology;

  if (topology->levels[0][0]->cpuset)

    return 0;

  hwloc_alloc_obj_cpusets(topology->levels[0][0]);
  hwloc_setup_pu_level(topology, hwloc_fallback_nbprocessors(topology));
  if (topology->is_thissystem)
    hwloc_add_uname_info(topology);
  return 1;
}

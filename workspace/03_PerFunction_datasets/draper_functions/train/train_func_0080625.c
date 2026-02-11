hwloc_set_proc_membind(hwloc_topology_t topology, hwloc_pid_t pid, hwloc_const_cpuset_t set, hwloc_membind_policy_t policy, int flags)
{
  hwloc_nodeset_t nodeset = hwloc_bitmap_alloc();
  int ret;

  if (hwloc_fix_membind_cpuset(topology, nodeset, set))
    ret = -1;
  else
    ret = hwloc_set_proc_membind_nodeset(topology, pid, nodeset, policy, flags);

  hwloc_bitmap_free(nodeset);
  return ret;
}

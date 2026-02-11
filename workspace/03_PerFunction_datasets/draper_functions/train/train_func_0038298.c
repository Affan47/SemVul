hwloc_get_proc_membind_nodeset(hwloc_topology_t topology, hwloc_pid_t pid, hwloc_nodeset_t nodeset, hwloc_membind_policy_t * policy, int flags)
{
  if (topology->binding_hooks.get_proc_membind)
    return topology->binding_hooks.get_proc_membind(topology, pid, nodeset, policy, flags);

  errno = ENOSYS;
  return -1;
}

hwloc_propagate_bridge_depth(hwloc_topology_t topology, hwloc_obj_t root, unsigned depth)
{
  hwloc_obj_t child = root->first_child;
  while (child) {
    if (child->type == HWLOC_OBJ_BRIDGE) {
      child->attr->bridge.depth = depth;
      hwloc_propagate_bridge_depth(topology, child, depth+1);
    }
    child = child->next_sibling;
  }
}

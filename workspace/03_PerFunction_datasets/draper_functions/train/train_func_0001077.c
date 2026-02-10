remove_empty(hwloc_topology_t topology, hwloc_obj_t *pobj)
{
  hwloc_obj_t obj = *pobj, child, *pchild;

  for_each_child_safe(child, obj, pchild)
    remove_empty(topology, pchild);

  if (obj->type != HWLOC_OBJ_NODE
      && !obj->first_child
      && !hwloc_obj_type_is_io(obj->type) && obj->type != HWLOC_OBJ_MISC
      && obj->cpuset
      && hwloc_bitmap_iszero(obj->cpuset)) {

    hwloc_debug("%s", "\nRemoving empty object ");
    print_object(topology, 0, obj);
    unlink_and_free_single_object(pobj);
  }
}

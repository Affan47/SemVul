find_my_numa_node(void)
{
    hwloc_obj_t obj;
    hwloc_bitmap_t cpuset;

    if (NULL != my_numa_node) {
        return OMPI_SUCCESS;
    }


    cpuset = hwloc_bitmap_alloc();
    if (NULL == cpuset) {
        return OMPI_ERR_OUT_OF_RESOURCE;
    }
    if (0 != hwloc_get_cpubind(opal_hwloc_topology, cpuset, 0)) {
        hwloc_bitmap_free(cpuset);
        return OMPI_ERR_NOT_AVAILABLE;
    }


    obj = find_numa_node(cpuset);
    hwloc_bitmap_free(cpuset);
    if (NULL == obj) {
        return OMPI_ERR_NOT_AVAILABLE;
    }


    my_numa_node = obj;
    num_numa_nodes = hwloc_get_nbobjs_by_type(opal_hwloc_topology,
                                              HWLOC_OBJ_NODE);
    return OMPI_SUCCESS;

}

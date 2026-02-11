opal_hwloc_base_memory_set(opal_hwloc_base_memory_segment_t *segments,
                               size_t num_segments)
{
    int rc = OPAL_SUCCESS;
    char *msg = NULL;
    size_t i;
    hwloc_cpuset_t cpuset = NULL;


    if (NULL == opal_hwloc_topology) {
        msg = "hwloc_set_area_membind() failure - topology not available";
        return opal_hwloc_base_report_bind_failure(__FILE__, __LINE__,
                                                   msg, rc);
    }


    cpuset = hwloc_bitmap_alloc();
    if (NULL == cpuset) {
        rc = OPAL_ERR_OUT_OF_RESOURCE;
        msg = "hwloc_bitmap_alloc() failure";
        goto out;
    }
    hwloc_get_cpubind(opal_hwloc_topology, cpuset, 0);
    for (i = 0; i < num_segments; ++i) {
        if (0 != hwloc_set_area_membind(opal_hwloc_topology,
                                        segments[i].mbs_start_addr,
                                        segments[i].mbs_len, cpuset,
                                        HWLOC_MEMBIND_BIND,
                                        HWLOC_MEMBIND_STRICT)) {
            rc = OPAL_ERROR;
            msg = "hwloc_set_area_membind() failure";
            goto out;
        }
    }

 out:
    if (NULL != cpuset) {
        hwloc_bitmap_free(cpuset);
    }
    if (OPAL_SUCCESS != rc) {
        return opal_hwloc_base_report_bind_failure(__FILE__, __LINE__, msg, rc);
    }
    return OPAL_SUCCESS;
}

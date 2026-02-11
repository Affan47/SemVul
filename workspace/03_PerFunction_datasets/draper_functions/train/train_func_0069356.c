sum_const(opal_hwloc_summary_t *ptr)
{
    ptr->num_objs = 0;
    ptr->rtype = 0;
    OBJ_CONSTRUCT(&ptr->sorted_by_dist_list, opal_list_t);
}

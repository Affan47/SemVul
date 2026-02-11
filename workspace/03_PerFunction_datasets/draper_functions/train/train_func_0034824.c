set_max_array_range_semnode_size_pa(const Array_range_semnode *range,
				    const Memory_access_region_table *martbl,
				    const int dim,
				    int lower[],
				    int upper[])
{
    int t;

    if (range->lower_tree == NULL || !semtree_is_const(range->lower_tree)) {
        t = get_memory_access_region_table_lower_size_one_dim(martbl,dim);
    } else {
        t = (int)semtree_to_double(range->lower_tree);
    }
    if (lower[dim] > t) {
        lower[dim] = t;
    }

    if (range->upper_tree == NULL || !semtree_is_const(range->upper_tree)) {
        t = get_memory_access_region_table_upper_size_one_dim(martbl,dim);
    } else {
        t = (int)semtree_to_double(range->upper_tree);
    }
    if (upper[dim] < t) {
        upper[dim] = t;
    }
}

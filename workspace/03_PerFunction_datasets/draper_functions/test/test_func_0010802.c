is_added_local_node_pa(List **local_node, Memory_access_region_table *martbl)
{
    if(martbl->kind == KIND_ARRAY) {
	return is_added_local_node(local_node, martbl->tbl.a);
    } else {
	return FALSE;
    }
}

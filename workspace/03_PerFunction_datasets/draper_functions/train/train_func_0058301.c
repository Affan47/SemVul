check_for_full_delete(sh_node_pt x)
{
    int level = x->level;
    return ((level & READY_FOR_FREE) ||
	    (CASIO(&x->level, level, level | READY_FOR_FREE) != level));
}

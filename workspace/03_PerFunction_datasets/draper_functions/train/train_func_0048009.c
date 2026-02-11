vdtree_busy_pop(ViewDir *vd)
{
	if (VDTREE(vd)->busy_ref == 1) set_cursor(vd->view, -1);
	if (VDTREE(vd)->busy_ref > 0) VDTREE(vd)->busy_ref--;
}

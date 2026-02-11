delete_vit_point(cst_vit_point *vp)
{
    int i;

    if (vp)
    {
	if (vp->paths)
	    delete_vit_path(vp->paths);
	if (vp->num_states != 0)
	{
	    for (i=0; i<vp->num_states; i++)
		if (vp->state_paths[i])
		    delete_vit_path(vp->state_paths[i]);
	    cst_free(vp->state_paths);
	}
	delete_vit_cand(vp->cands);
	delete_vit_point(vp->next);
	cst_free(vp);
    }
}

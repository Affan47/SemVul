translate_quad(struct multtree *tree,
		   double numberx,
		   double numbery, double numberz, int n_leafs)
{
    int total = 0, i, ii;

    if (tree == NULL)
	return 0;
    if (tree->data == NULL)
	return 0;

    if (tree->leafs != NULL) {
	((struct quaddata *)(tree->data))->x_orig -= numberx;
	((struct quaddata *)(tree->data))->y_orig -= numbery;
	((struct quaddata *)(tree->data))->xmax -= numberx;
	((struct quaddata *)(tree->data))->ymax -= numbery;
	for (ii = 0; ii < n_leafs; ii++)
	    total +=
		translate_quad(tree->leafs[ii], numberx, numbery, numberz,
			       n_leafs);
    }
    else {
	((struct quaddata *)(tree->data))->x_orig -= numberx;
	((struct quaddata *)(tree->data))->y_orig -= numbery;
	((struct quaddata *)(tree->data))->xmax -= numberx;
	((struct quaddata *)(tree->data))->ymax -= numbery;
	for (i = 0; i < ((struct quaddata *)(tree->data))->n_points; i++) {
	    ((struct quaddata *)(tree->data))->points[i].x -= numberx;
	    ((struct quaddata *)(tree->data))->points[i].y -= numbery;
	    ((struct quaddata *)(tree->data))->points[i].z -= numberz;
	}

	return 1;
    }

    return total;
}

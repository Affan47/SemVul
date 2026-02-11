gv_free_vectmem(geovect * fv)
{
    geoline *gln, *tmpln;

    G_free((void *)fv->filename);
    fv->filename = NULL;

    if (fv->lines) {
	for (gln = fv->lines; gln;) {
	    if (gln->dims == 2) {
		sub_Vectmem(gln->npts * sizeof(Point2));
		G_free(gln->p2);
	    }

	    if (gln->dims == 3) {
		G_free(gln->p3);
	    }

	    tmpln = gln;
	    gln = gln->next;
	    sub_Vectmem(sizeof(geoline));
	    G_free(tmpln);
	}

	fv->n_lines = 0;
	fv->lines = NULL;
    }

    return;
}

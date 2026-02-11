ofps_add_fixed(
ofps *s
) {
	int e, di = s->di;
	int i, j, ii;


	if (s->fnp == 0)
		return 0;

	if (s->verb)
		printf("Adding %d unique fixed points\n",s->fnp);

	for (i = 0; i < s->fnp; i++) {
		node *p = s->n[i];


		ofps_clip_point(s, s->ufx[i]->p, s->ufx[i]->p);

		for (e = 0; e < di; e++) {
			p->op[e] = p->p[e] = s->ufx[i]->p[e];
			p->v[e] = s->ufx[i]->v[e];
		}


		det_node_gsurf(s, p, p->p);

		p->fx = 1;


		if (add_node2voronoi(s, s->np, 1)) {


			warning("Adding a fixed point failed to hit any vertexes, and no points to swap with!");
			return 1;
		}

		if (s->verb)
			printf("%cAdded fixed %d/%d",cr_char,i,s->fnp); fflush(stdout);

#ifdef DUMP_STRUCTURE
		printf("Done node %d\n",s->np);
		dump_node_vtxs(s, 0);
		printf("=========================================================================\n");
#endif
#ifdef DUMP_PLOT_SEED
		dump_image(s, PERC_PLOT, DO_WAIT, DUMP_VTX, DUMP_PLA, 0, -1);
#endif
	}

	return 0;
}

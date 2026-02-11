do_weeks_code(WEpolyhedron **wepolyhedron, point oo, proj_matrix *gen_list,
	      int n, int met, int slice)
{
	int i;
	for (i=0; i<4; ++i)	origin[i] = oo[i];

	heapcount = 0;
	metric = met;
	*wepolyhedron = &the_polyhedron;


	make_cube(*wepolyhedron);
	initialize_polyhedron(*wepolyhedron, gen_list, n);
	if (find_Dirichlet_domain(*wepolyhedron) == 0) 	*wepolyhedron = NULL;
	else {
	    if (debug == 2) print_poly(*wepolyhedron);
	    number_faces(*wepolyhedron);
	    }
	if (slice && (metric == DG_HYPERBOLIC)) slice_off_cusps(*wepolyhedron);
}

print_vertices(polyhedron)
WEpolyhedron *polyhedron;
{
	WEvertex	*vertex;
	fprintf(stderr, "Vertices:\n");
	for (vertex=polyhedron->vertex_list; vertex; vertex=vertex->next)
	    fprintf(stderr, "%f\t%f\t%f\t%f\n",vertex->x[0], vertex->x[1], vertex->x[2], vertex->x[3]);
}

gen_triangle(
    int num_isolines,
    struct iso_curve *iso_lines,
    poly_struct **p_polys,
    edge_struct **p_edges)
{
    int i, j, grid_x_max = iso_lines->p_count;
    edge_struct *p_edge1, *p_edge2, *edge0, *edge1, *edge2, *pe_tail,
	   *pe_tail2, *pe_temp;
    poly_struct *pp_tail, *lower_tri, *upper_tri;

    struct coordinate GPHUGE *p_vrtx1, GPHUGE * p_vrtx2;

    (*p_polys) = pp_tail = NULL;
    (*p_edges) = pe_tail = NULL;

    p_vrtx1 = iso_lines->points;
    p_edge1 = pe_tail = NULL;


    for (j = 0; j < grid_x_max - 1; j++)
	add_edge(p_vrtx1 + j, p_vrtx1 + j + 1, &p_edge1, &pe_tail);

    (*p_edges) = p_edge1;


    for (i = 1; i < num_isolines; i++) {

	iso_lines = iso_lines->next;

	p_vrtx2 = iso_lines->points;
	p_edge2 = pe_tail2 = NULL;
	pe_temp = p_edge1;


	edge2 = add_edge(p_vrtx1, p_vrtx2, p_edges, &pe_tail);

	for (j = 0; j < grid_x_max - 1; j++) {


	    edge0 = edge2;

	    if (pe_temp && pe_temp->vertex[0] == p_vrtx1 + j) {

		edge2 = pe_temp;
		pe_temp = pe_temp->next;
	    } else {
		edge2 = NULL;
	    }


	    edge1 = add_edge(p_vrtx1 + j + 1, p_vrtx2 + j, p_edges, &pe_tail);
	    if (edge1)
		edge1->position = DIAGONAL;


	    lower_tri = add_poly(edge0, edge1, edge2, p_polys, &pp_tail);


	    edge0 = edge1;


	    edge1 = add_edge(p_vrtx2 + j, p_vrtx2 + j + 1, &p_edge2, &pe_tail2);


	    edge2 = add_edge(p_vrtx1 + j + 1, p_vrtx2 + j + 1, p_edges, &pe_tail);


	    upper_tri = add_poly(edge0, edge1, edge2, p_polys, &pp_tail);
	}

	if (p_edge2) {


	    if ((*p_edges)) {
		pe_tail->next = p_edge2;
		pe_tail = pe_tail2;
	    } else {
		(*p_edges) = p_edge2;
		pe_tail = pe_tail2;
	    }
	}


	p_edge1 = p_edge2;
	p_vrtx1 = p_vrtx2;
    }


    pe_temp = (*p_edges);

    while (pe_temp) {
	if ((!(pe_temp->poly[0])) || (!(pe_temp->poly[1])))
	    (pe_temp->position) = BOUNDARY;
	pe_temp = pe_temp->next;
    }
}

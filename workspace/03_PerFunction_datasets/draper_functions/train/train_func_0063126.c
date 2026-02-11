calculate_supertriangle(std::vector<CL_DelauneyTriangulator_Vertex *> &vertices, CL_DelauneyTriangulator_Triangle &super_triangle)
{


	double min_x = 0.0;
	double max_x = 0.0;
	double min_y = 0.0;
	double max_y = 0.0;
	bool first_point = true;

	std::vector<CL_DelauneyTriangulator_Vertex *>::size_type index_vertices, num_vertices;
	num_vertices = vertices.size();
	for (index_vertices = 0; index_vertices < num_vertices; index_vertices++)
	{
		CL_DelauneyTriangulator_Vertex *cur_vertex = vertices[index_vertices];

		if (!first_point)
		{
			if (min_x > cur_vertex->x) min_x = cur_vertex->x;
			if (max_x < cur_vertex->x) max_x = cur_vertex->x;
			if (min_y > cur_vertex->y) min_y = cur_vertex->y;
			if (max_y < cur_vertex->y) max_y = cur_vertex->y;
		}
		else
		{
			first_point = false;
			min_x = cur_vertex->x;
			max_x = cur_vertex->x;
			min_y = cur_vertex->y;
			max_y = cur_vertex->y;
		}
	}


	super_triangle.vertex_A->x = min_x-1;
	super_triangle.vertex_A->y = min_y-1;
	super_triangle.vertex_A->data = 0;

	super_triangle.vertex_B->x = max_x+(max_x-min_x)+1;
	super_triangle.vertex_B->y = min_y-1;
	super_triangle.vertex_B->data = 0;

	super_triangle.vertex_C->x = min_x-1;
	super_triangle.vertex_C->y = max_y+(max_y-min_y)+1;
	super_triangle.vertex_C->data = 0;
}

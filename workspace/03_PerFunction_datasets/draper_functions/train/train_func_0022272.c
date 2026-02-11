mark_shortest_path (Vertex *v1, Vertex *v2)
{
	Graph::e_const_iterator eit;
	Graph::v_iterator vit;


	for (vit = v_begin (); vit != v_end (); ++vit)
		(*vit)->mark = 0;
	v1->mark = 1;

	while (1) {

		for (vit = v_begin (); vit != v_end (); ++vit)
			if ((*vit)->mark < 1)
				break;
		if (vit == v_end ())
			break;


		for (vit = v_begin (); vit != v_end (); ++vit) {
			Vertex *v = *vit;

			if (v->mark > 0)
				continue;
			v->mark = 0;
			eit = v->e_begin ();
			for (; eit != v->e_end (); ++eit) {
				Edge *e = *eit;
				Vertex *alt = v->opposite (e);
				if (e->directed && (v != e->w))
					continue;

				if (alt->mark < 1)
					continue;
				if (((alt->mark + e->weight) < -v->mark) ||
							(v->mark == 0))
					v->mark = -(alt->mark + e->weight);
			}
		}


		Vertex *min = v1;
		bool none_yet = true;
		int min_val = 0;
		for (vit = v_begin (); vit != v_end (); ++vit) {
			if ((*vit == v1) || ((*vit)->mark >= 0))
				continue;
			if ((min_val > -(*vit)->mark) || none_yet) {
				min = *vit;
				min_val = -min->mark;
				none_yet = false;
			}
		}
		if (min == v1)
			break;


		min->mark = -min->mark;

		if (min == v2)
			break;
	}


	for (vit = v_begin (); vit != v_end (); ++vit) {
		Vertex *v = *vit;

		if (v->mark > 0)
			v->mark -= 1;
		else
			v->mark = -1;
	}
}

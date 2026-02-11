_synctex_eq_deepest_container(synctex_point_t hitPoint,synctex_node_t node, synctex_bool_t visible) {
	if (node) {
		synctex_node_t result = NULL;
		synctex_node_t child = NULL;
		switch(node->class->type) {
			case synctex_node_type_vbox:
			case synctex_node_type_hbox:

				if ((child = SYNCTEX_CHILD(node))) {
					do {
						if ((result = _synctex_eq_deepest_container(hitPoint,child,visible))) {
							return result;
						}
					} while((child = SYNCTEX_SIBLING(child)));
				}

				if (_synctex_point_in_box(hitPoint,node,visible)) {


					if ((node->class->type == synctex_node_type_vbox) && (child = SYNCTEX_CHILD(node))) {
						int bestDistance = INT_MAX;
						do {
							if (SYNCTEX_CHILD(child)) {
								int distance = _synctex_node_distance_to_point(hitPoint,child,visible);
								if (distance < bestDistance) {
									bestDistance = distance;
									node = child;
								}
							}
						} while((child = SYNCTEX_SIBLING(child)));
					}
					return node;
				}
		}
	}
	return NULL;
}

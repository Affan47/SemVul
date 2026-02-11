model_create_bsp_collision_tree()
{

	size_t i;
	bool slot_found = false;

	for ( i = 0; i < Bsp_collision_tree_list.size(); ++i ) {
		if ( !Bsp_collision_tree_list[i].used ) {
			slot_found = true;
			break;
		}
	}

	if ( slot_found ) {
		Bsp_collision_tree_list[i].used = true;

		return (int)i;
	}

	bsp_collision_tree tree;

	tree.used = true;
	Bsp_collision_tree_list.push_back(tree);

	return Bsp_collision_tree_list.size() - 1;
}

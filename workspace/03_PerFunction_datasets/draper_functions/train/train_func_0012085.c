obj_sort_and_collide()
{
	if (Cmdline_dis_collisions)
		return;

	if ( !(Game_detail_flags & DETAIL_FLAG_COLLISION) )
		return;

	SCP_vector<int> sort_list_y;
	SCP_vector<int> sort_list_z;

	sort_list_y.clear();
	obj_quicksort_colliders(&Collision_sort_list, 0, Collision_sort_list.size() - 1, 0);
	obj_find_overlap_colliders(&sort_list_y, &Collision_sort_list, 0, false);

	sort_list_z.clear();
	obj_quicksort_colliders(&sort_list_y, 0, sort_list_y.size() - 1, 1);
	obj_find_overlap_colliders(&sort_list_z, &sort_list_y, 1, false);

	sort_list_y.clear();
	obj_quicksort_colliders(&sort_list_z, 0, sort_list_z.size() - 1, 2);
	obj_find_overlap_colliders(&sort_list_y, &sort_list_z, 2, true);
}

obj_all_collisions_retime(int checkdly)


{
	obj_pair *parent, *tmp;

	parent = &pair_used_list;
	tmp = parent->next;


	while (tmp != NULL)
	{
		tmp->next_check_time = timestamp(checkdly);
		tmp = tmp->next;
	}
}

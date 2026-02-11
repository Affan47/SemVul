dock_move_docked_children_tree(object *objp, object *parent_objp)
{

	if (objp->flags & OF_DOCKED_ALREADY_HANDLED)
		return;


	objp->flags |= OF_DOCKED_ALREADY_HANDLED;


	if (parent_objp != NULL)
	{

		obj_move_one_docked_object(objp, parent_objp);
	}


	for (dock_instance *ptr = objp->dock_list; ptr != NULL; ptr = ptr->next)
	{

		dock_move_docked_children_tree(ptr->docked_objp, objp);
	}
}

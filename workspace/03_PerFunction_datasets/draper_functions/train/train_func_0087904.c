dock_dock_objects(object *objp1, int dockpoint1, object *objp2, int dockpoint2)
{
#ifndef NDEBUG
	if ((dock_find_instance(objp1, objp2) != NULL) || (dock_find_instance(objp2, objp1) != NULL))
	{
		Error(LOCATION, "Trying to dock an object that's already docked!\n");
	}

	if ((dock_find_instance(objp1, dockpoint1) != NULL) || (dock_find_instance(objp2, dockpoint2) != NULL))
	{
		Error(LOCATION, "Trying to dock to a dockpoint that's in use!\n");
	}
#endif


	dock_add_instance(objp1, dockpoint1, objp2);
	dock_add_instance(objp2, dockpoint2, objp1);
}

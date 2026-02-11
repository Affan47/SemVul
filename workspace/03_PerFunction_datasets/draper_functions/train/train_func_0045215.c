has_reached_floor (T_SGEObject * object)
{
	if (object->y >= object->dest_y) {
		object->y = object->dest_y;
		return -1;
	}

	return 0;
}

COM_Get_location_with_pointer(int *wx, int *wy, int *button)
{
    int ret = 0;

    if (driver->Get_with_pointer) {
	ret = (*driver->Get_with_pointer) (wx, wy, button);
	if (*button >= 1 && *button <= 3)
	    *button = mouse_button[*button - 1];
    }

    return ret;
}

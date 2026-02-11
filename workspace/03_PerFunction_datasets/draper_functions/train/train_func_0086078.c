dig_Rd_P_area(struct Plus_head *Plus, int n, GVFILE * fp)
{
    int cnt;
    P_AREA *ptr;

#ifdef GDEBUG
    G_debug(3, "dig_Rd_P_area(): n = %d", n);
#endif

    if (0 >= dig__fread_port_P(&cnt, 1, fp))
	return (-1);

    if (cnt == 0) {
	Plus->Area[n] = NULL;
	return 0;
    }

    ptr = dig_alloc_area();


    ptr->n_lines = cnt;

    if (dig_area_alloc_line(ptr, ptr->n_lines) == -1)
	return -1;

    if (ptr->n_lines)
	if (0 >= dig__fread_port_P(ptr->lines, ptr->n_lines, fp))
	    return -1;


    if (0 >= dig__fread_port_P(&(ptr->n_isles), 1, fp))
	return -1;

    if (dig_area_alloc_isle(ptr, ptr->n_isles) == -1)
	return -1;

    if (ptr->n_isles)
	if (0 >= dig__fread_port_P(ptr->isles, ptr->n_isles, fp))
	    return -1;


    if (0 >= dig__fread_port_P(&(ptr->centroid), 1, fp))
	return -1;

    if (0 >= dig__fread_port_D(&(ptr->N), 1, fp))
	return -1;
    if (0 >= dig__fread_port_D(&(ptr->S), 1, fp))
	return -1;
    if (0 >= dig__fread_port_D(&(ptr->E), 1, fp))
	return -1;
    if (0 >= dig__fread_port_D(&(ptr->W), 1, fp))
	return -1;

    if (Plus->with_z) {
	if (0 >= dig__fread_port_D(&(ptr->T), 1, fp))
	    return -1;
	if (0 >= dig__fread_port_D(&(ptr->B), 1, fp))
	    return -1;
    }
    else {
	ptr->T = 0.0;
	ptr->B = 0.0;
    }

    Plus->Area[n] = ptr;

    return (0);
}

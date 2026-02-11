dig_Wr_spindx_head(GVFILE * fp, struct Plus_head *ptr)
{
    unsigned char buf[5];
    long length = 42;

    dig_rewind(fp);
    dig_set_cur_port(&(ptr->spidx_port));


    buf[0] = GV_SIDX_VER_MAJOR;
    buf[1] = GV_SIDX_VER_MINOR;
    buf[2] = GV_SIDX_EARLIEST_MAJOR;
    buf[3] = GV_SIDX_EARLIEST_MINOR;
    buf[4] = ptr->spidx_port.byte_order;
    if (0 >= dig__fwrite_port_C(buf, 5, fp))
	return (-1);


    if (0 >= dig__fwrite_port_L(&length, 1, fp))
	return (0);


    buf[0] = ptr->spidx_with_z;
    if (0 >= dig__fwrite_port_C(buf, 1, fp))
	return (-1);


    if (0 >= dig__fwrite_port_L(&(ptr->Node_spidx_offset), 1, fp))
	return (-1);
    if (0 >= dig__fwrite_port_L(&(ptr->Edge_spidx_offset), 1, fp))
	return (-1);
    if (0 >= dig__fwrite_port_L(&(ptr->Line_spidx_offset), 1, fp))
	return (-1);
    if (0 >= dig__fwrite_port_L(&(ptr->Area_spidx_offset), 1, fp))
	return (-1);
    if (0 >= dig__fwrite_port_L(&(ptr->Isle_spidx_offset), 1, fp))
	return (-1);
    if (0 >= dig__fwrite_port_L(&(ptr->Volume_spidx_offset), 1, fp))
	return (-1);
    if (0 >= dig__fwrite_port_L(&(ptr->Hole_spidx_offset), 1, fp))
	return (-1);

    G_debug(3, "spidx offset node = %ld line = %ld, area = %ld isle = %ld",
	    ptr->Node_spidx_offset, ptr->Line_spidx_offset,
	    ptr->Area_spidx_offset, ptr->Isle_spidx_offset);


    if (0 >= dig__fwrite_port_L(&(ptr->coor_size), 1, fp))
	return (-1);

    G_debug(2, "spidx body offset %ld", dig_ftell(fp));

    return (0);
}

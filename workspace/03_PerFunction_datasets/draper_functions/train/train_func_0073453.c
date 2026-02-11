V1__rewrite_line_nat(struct Map_info *Map,
			  long offset,
			  int type,
			  struct line_pnts *points, struct line_cats *cats)
{
    int i, n_points;
    char rhead, nc;
    short field;
    GVFILE *dig_fp;

    dig_set_cur_port(&(Map->head.port));
    dig_fp = &(Map->dig_fp);

    if (dig_fseek(dig_fp, offset, 0) == -1)
	return -1;


    rhead = (char)dig_type_to_store(type);
    rhead <<= 2;
    if (cats->n_cats > 0) {
	rhead |= 0x02;
    }
    rhead |= 0x01;

    if (0 >= dig__fwrite_port_C(&rhead, 1, dig_fp)) {
	return -1;
    }

    if (cats->n_cats > 0) {
	if (Map->head.Version_Minor == 1) {
	    if (0 >= dig__fwrite_port_I(&(cats->n_cats), 1, dig_fp))
		return -1;
	}
	else {
	    nc = (char)cats->n_cats;
	    if (0 >= dig__fwrite_port_C(&nc, 1, dig_fp))
		return -1;
	}

	if (cats->n_cats > 0) {
	    if (Map->head.Version_Minor == 1) {
		if (0 >=
		    dig__fwrite_port_I(cats->field, cats->n_cats, dig_fp))
		    return -1;
	    }
	    else {
		for (i = 0; i < cats->n_cats; i++) {
		    field = (short)cats->field[i];
		    if (0 >= dig__fwrite_port_S(&field, 1, dig_fp))
			return -1;
		}
	    }
	    if (0 >= dig__fwrite_port_I(cats->cat, cats->n_cats, dig_fp))
		return -1;
	}
    }

    if (type & GV_POINTS) {
	n_points = 1;
    }
    else {
	n_points = points->n_points;
	if (0 >= dig__fwrite_port_I(&n_points, 1, dig_fp))
	    return -1;
    }

    if (0 >= dig__fwrite_port_D(points->x, n_points, dig_fp))
	return -1;
    if (0 >= dig__fwrite_port_D(points->y, n_points, dig_fp))
	return -1;

    if (Map->head.with_z) {
	if (0 >= dig__fwrite_port_D(points->z, n_points, dig_fp))
	    return -1;
    }

    if (0 != dig_fflush(dig_fp))
	return -1;

    return offset;
}

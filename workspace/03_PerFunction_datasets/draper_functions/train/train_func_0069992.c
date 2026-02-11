gpd_obj_site_attr(geosurf * gs, geosite * gp, geopoint * gpt, Point3 site)
{
    float size, z, y, x, z_scale, z_offset;
    int marker, color, i, ii, iii;
    int use_attr, has_drawn;
    int _put_aside_;

    _put_aside_ = 0;
    _cur_size_ = gp->size;

    z_scale = GS_global_exag();
    z_offset = 0.0;

    has_drawn = 0;

    for (i = 0; i < GPT_MAX_ATTR; i++) {
	color = gp->color;
	marker = gp->marker;
	size = gp->size;
	use_attr = 0;

	if (gp->use_attr[i] & ST_ATT_COLOR) {
	    use_attr = 1;
	    color = gpt->color[i];
	}

	if (gp->use_attr[i] & ST_ATT_MARKER) {
	    use_attr = 1;
	    marker = gpt->marker[i];
	}

	if (gp->use_attr[i] & ST_ATT_SIZE) {
	    use_attr = 1;
	    size = gpt->size[i] * gp->size;
	    if (gp->marker == ST_HISTOGRAM)
		_put_aside_ = 1;
	}


	if (gpt->highlight_color)
	    color = gpt->highlight_color_value;
	if (gpt->highlight_marker)
	    marker = gpt->highlight_marker_value;
	if (gpt->highlight_size)
	    size *= gpt->highlight_size_value;


	if (_put_aside_) {
	    if (use_attr == 1) {
		has_drawn = 1;


		x = site[X];
		y = site[Y];

		ii = (int)(sqrt(i));
		iii = ii * ii + ii;

		if (i <= iii) {
		    site[X] += ii * 2.2 * gp->size;
		    site[Y] += (i - ii) * 2.2 * gp->size;
		}
		else {
		    site[X] += (ii - (i - iii)) * 2.2 * gp->size;
		    site[Y] += ii * 2.2 * gp->size;

		}

		gpd_obj(gs, color, size, marker, site);

		site[X] = x;
		site[Y] = y;
	    }
	}
	else {
	    if (i > 0)
		z_offset += size;
	    if (use_attr == 1) {
		has_drawn = 1;

		z = site[Z];
		site[Z] += z_offset / z_scale;

		gpd_obj(gs, color, size, marker, site);

		site[Z] = z;
	    }

	    z_offset += size;
	}
    }

    if (has_drawn == 0)
	gpd_obj(gs, color, size, marker, site);

    return (0);
}

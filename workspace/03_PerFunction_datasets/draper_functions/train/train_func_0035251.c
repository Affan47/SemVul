fringe_changes(ModeInfo * mi, fringe_node_c * vertex,
	       unsigned side, vertex_type_c vtype,
	       fringe_node_c ** right, fringe_node_c ** far,
	       fringe_node_c ** left)
{
	fringe_node_c *v, *f = (fringe_node_c *) NULL;
	unsigned    result = FC_NEW_FAR;

	if (far)
		*far = 0;
	if (fills_vertex(mi, vtype, vertex)) {
		result |= FC_CUT_THIS;
	} else if (side == S_LEFT) {
		result |= FC_NEW_RIGHT;
		if (right)
			*right = 0;
	} else {
		result |= FC_NEW_LEFT;
		if (left)
			*left = 0;
	}

	if (!(result & FC_NEW_LEFT)) {
		v = vertex->next;
		if (left)
			*left = v;
		if (fills_vertex(mi, VT_LEFT(vtype), v)) {
			result = (result & ~FC_NEW_FAR) | FC_CUT_LEFT;
			f = v->next;
			if (far)
				*far = f;
		}
	}
	if (!(result & FC_NEW_RIGHT)) {
		v = vertex->prev;
		if (right)
			*right = v;
		if (fills_vertex(mi, VT_RIGHT(vtype), v)) {
			result = (result & ~FC_NEW_FAR) | FC_CUT_RIGHT;
			f = v->prev;
			if (far)
				*far = f;
		}
	}
	if (!(result & FC_NEW_FAR)
	    && fills_vertex(mi, VT_FAR(vtype), f)) {
		result |= FC_CUT_FAR;
		result &= (~FC_NEW_LEFT & ~FC_NEW_RIGHT);
		if (right && (result & FC_CUT_LEFT))
			*right = f->next;
		if (left && (result & FC_CUT_RIGHT))
			*left = f->prev;
	}
	if (((result & FC_CUT_LEFT) && (result & FC_CUT_RIGHT))
	    || ((result & FC_CUT_THIS) && (result & FC_CUT_FAR)))
		result |= FC_BAG;
	return result;
}

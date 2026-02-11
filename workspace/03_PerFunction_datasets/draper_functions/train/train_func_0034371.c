CM_TransformedPointContents (const vec3_t p, int headnode, const vec3_t origin, const vec3_t angles)
{
	vec3_t		p_l;
	vec3_t		temp;
	vec3_t		forward, right, up;
	int			l;


	VectorSubtract (p, origin, p_l);


	if (headnode != box_headnode &&
	(angles[0] || angles[1] || angles[2]) )
	{
		AngleVectors (angles, forward, right, up);

		VectorCopy (p_l, temp);
		p_l[0] = DotProduct (temp, forward);
		p_l[1] = -DotProduct (temp, right);
		p_l[2] = DotProduct (temp, up);
	}

	l = CM_PointLeafnum_r (p_l, headnode);

	return map_leafs[l].contents;
}

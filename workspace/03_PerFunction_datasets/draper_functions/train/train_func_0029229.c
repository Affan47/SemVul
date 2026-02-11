R_StaticLightPoint (vec3_t p, vec3_t color)
{
	float		r;
	vec3_t		end;

	if (!r_worldmodel->lightdata)
	{
		color[0] = color[1] = color[2] = 1.0;
		return;
	}

	end[0] = p[0];
	end[1] = p[1];
	end[2] = p[2] - 2048;

	r = RecursiveLightPoint (r_worldmodel->nodes, p, end);

	if (r == -1)
	{
		VectorCopy (vec3_origin, color);
	}
	else
	{
		VectorCopy (pointcolor, color);
	}
}

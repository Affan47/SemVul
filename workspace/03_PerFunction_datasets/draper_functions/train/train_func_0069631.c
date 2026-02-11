R_AddGLSLShadedWarpSurfToVArray (msurface_t *surf, float scroll)
{
	glpoly_t *p = surf->polys;
	float	*v;
	int		i;

	for (; p; p = p->chain)
	{

		VArray = &VArrayVerts[0];
		VertexCounter = 0;

		for (v = p->verts[0], i = 0 ; i < p->numverts; i++, v += VERTEXSIZE)
		{

			VArray[0] = v[0];
			VArray[1] = v[1];
			VArray[2] = v[2];


			VArray[3] = v[3] + scroll;
			VArray[4] = v[4];


			VArray += VertexSizes[VERT_COLOURED_TEXTURED];
			VertexCounter++;
		}
	}


	R_DrawVarrays(GL_POLYGON, 0, VertexCounter);
}

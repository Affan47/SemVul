R_AddSurfToVArray (msurface_t *surf)
{
	glpoly_t *p = surf->polys;
	float	*v;
	int i;

	for (; p; p = p->chain)
	{

		VArray = &VArrayVerts[0];
		VertexCounter = 0;

		for (v = p->verts[0], i = 0 ; i < p->numverts; i++, v += VERTEXSIZE)
		{

			VArray[0] = v[0];
			VArray[1] = v[1];
			VArray[2] = v[2];


			VArray += VertexSizes[VERT_NO_TEXTURE];
			VertexCounter++;
		}


		R_DrawVarrays(GL_POLYGON, 0, VertexCounter);
	}
}

R_DrawRSSurfaces (void)
{
	msurface_t	*s = r_rscript_surfaces;

	if(!s)
		return;

	if (!r_shaders->integer)
	{
		r_rscript_surfaces = NULL;
		return;
	}

	qglDepthMask(false);
	qglShadeModel (GL_SMOOTH);

	qglEnable(GL_POLYGON_OFFSET_FILL);
	qglPolygonOffset(-3, -2);

	for (; s; s = s->rscriptchain)
		RS_Surface(s);

	qglDisable(GL_POLYGON_OFFSET_FILL);

	GLSTATE_DISABLE_BLEND
	GLSTATE_DISABLE_ALPHATEST

	qglDepthMask(true);
}

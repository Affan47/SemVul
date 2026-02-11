Draw_Fill (float x, float y, float w, float h, const float rgba[])
{
	qglDisable (GL_TEXTURE_2D);

	qglDisable (GL_ALPHA_TEST);
	qglEnable (GL_BLEND);
	GLSTATE_ENABLE_BLEND;
	GLSTATE_DISABLE_ALPHATEST;
	qglColor4fv (rgba);

	qglBegin (GL_QUADS);
		qglVertex2f (x,y);
		qglVertex2f (x+w, y);
		qglVertex2f (x+w, y+h);
		qglVertex2f (x, y+h);
	qglEnd ();

	GLSTATE_DISABLE_BLEND;
	qglColor3f (1,1,1);
	qglEnable (GL_TEXTURE_2D);
}

gr_opengl_flash_alpha(int r, int g, int b, int a)
{
	if ( !(r || g || b || a) ) {
		return;
	}

	CLAMP(r, 0, 255);
	CLAMP(g, 0, 255);
	CLAMP(b, 0, 255);
	CLAMP(a, 0, 255);

	GL_state.SetTextureSource(TEXTURE_SOURCE_NONE);
	GL_state.SetAlphaBlendMode(ALPHA_BLEND_ALPHA_BLEND_ALPHA);
	GL_state.SetZbufferType(ZBUFFER_TYPE_NONE);

	int x1 = (gr_screen.clip_left + gr_screen.offset_x);
	int y1 = (gr_screen.clip_top + gr_screen.offset_y);
	int x2 = (gr_screen.clip_right + gr_screen.offset_x) + 1;
	int y2 = (gr_screen.clip_bottom + gr_screen.offset_y) + 1;

	GL_state.Color( (GLubyte)r, (GLubyte)g, (GLubyte)b, (GLubyte)a );

	opengl_draw_coloured_quad((GLint)x1, (GLint)y1, (GLint)x2, (GLint)y2);
}

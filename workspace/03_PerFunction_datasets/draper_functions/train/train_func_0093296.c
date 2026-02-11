gr_opengl_shade(int x, int y, int w, int h, bool resize)
{
	if (resize) {
		gr_resize_screen_pos(&x, &y);
		gr_resize_screen_pos(&w, &h);
	}

	int x1 = (gr_screen.offset_x + x);
	int y1 = (gr_screen.offset_y + y);
	int x2 = (gr_screen.offset_x + w);
	int y2 = (gr_screen.offset_y + h);

	if ( (x1 >= gr_screen.max_w) || (y1 >= gr_screen.max_h) ) {
		return;
	}

	CLAMP(x2, x1+1, gr_screen.max_w);
	CLAMP(y2, y1+1, gr_screen.max_h);

	GL_state.SetTextureSource(TEXTURE_SOURCE_NONE);
	GL_state.SetAlphaBlendMode(ALPHA_BLEND_ALPHA_BLEND_ALPHA);
	GL_state.SetZbufferType(ZBUFFER_TYPE_NONE);

	gr_opengl_set_2d_matrix();

	GL_state.Color( (GLubyte)gr_screen.current_shader.r, (GLubyte)gr_screen.current_shader.g,
				(GLubyte)gr_screen.current_shader.b, (GLubyte)gr_screen.current_shader.c );

	opengl_draw_coloured_quad((GLint)x1, (GLint)y1, (GLint)x2, (GLint)y2);

	gr_opengl_end_2d_matrix();
}

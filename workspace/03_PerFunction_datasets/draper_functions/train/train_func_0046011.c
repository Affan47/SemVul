gr_opengl_bm_set_render_target(int n, int face)
{
	if ( !Is_Extension_Enabled(OGL_EXT_FRAMEBUFFER_OBJECT) || Cmdline_no_fbo ) {
		return 0;
	}

	if (n == -1) {
		opengl_set_render_target(-1);
		return 1;
	}

	Assert( (n >= 0) && (n < MAX_BITMAPS) );

	int is_static = (bm_bitmaps[n].type == BM_TYPE_RENDER_TARGET_STATIC);

	if ( opengl_set_render_target(n, face, is_static) ) {
		return 1;
	}

	return 0;
}

gr_opengl_cleanup(int minimize)
{
	if ( !GL_initted ) {
		return;
	}

	if ( !Fred_running ) {
		gr_reset_clip();
		gr_clear();
		gr_flip();
		gr_clear();
		gr_flip();
		gr_clear();
	}

	GL_initted = false;

	opengl_tcache_flush();

#ifdef _WIN32
	HWND wnd = (HWND)os_get_window();

	if (GL_render_context) {
		if ( !wglMakeCurrent(NULL, NULL) ) {
			MessageBox(wnd, "SHUTDOWN ERROR", "error", MB_OK);
		}

		if ( !wglDeleteContext(GL_render_context) ) {
			MessageBox(wnd, "Unable to delete rendering context", "error", MB_OK);
		}

		GL_render_context = NULL;
	}
#endif

	opengl_minimize();

	if (minimize) {
#ifdef _WIN32
		if ( !Cmdline_fullscreen_window && !Cmdline_window ) {
			ChangeDisplaySettings(NULL, 0);
		}
#endif
	}
}

opengl_kill_all_render_targets()
{
	for (size_t i = 0; i < RenderTarget.size(); i++) {
		fbo_t *fbo = &RenderTarget[i];

		if (fbo->framebuffer_id) {
			vglDeleteFramebuffersEXT(1, &fbo->framebuffer_id);
			fbo->framebuffer_id = 0;
		}

		if (fbo->renderbuffer_id) {
			vglDeleteRenderbuffersEXT(1, &fbo->renderbuffer_id);
			fbo->renderbuffer_id = 0;
		}
	}

	RenderTarget.clear();
}

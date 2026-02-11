opengl_tcache_shutdown()
{
	opengl_kill_all_render_targets();

	opengl_tcache_flush();

	GL_textures_in = 0;
	GL_textures_in_frame = 0;

	if (Textures != NULL) {
		vm_free(Textures);
		Textures = NULL;
	}

	if (Tex_used_this_frame != NULL) {
		vm_free(Tex_used_this_frame);
		Tex_used_this_frame = NULL;
	}
}

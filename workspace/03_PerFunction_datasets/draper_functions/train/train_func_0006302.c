opengl_tcache_init()
{
	int i;

	GL_should_preload = 1;

	GL_min_texture_width = 16;
	GL_min_texture_height = 16;

	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &GL_max_texture_width);

	GL_max_texture_height = GL_max_texture_width;


	if (GL_max_texture_width < 1024) {
		Error(LOCATION, "A minimum texture size of \"1024x1024\" is required for FS2_Open but only \"%ix%i\" was found.  Can not continue.", GL_max_texture_width, GL_max_texture_height);
	}

	if (Textures == NULL) {
		Textures = (tcache_slot_opengl *) vm_malloc_q(MAX_BITMAPS * sizeof(tcache_slot_opengl));
	}

	if (Tex_used_this_frame == NULL) {
		Tex_used_this_frame = (int *) vm_malloc_q(MAX_BITMAPS * sizeof(int));
	}

	if ( !Textures || !Tex_used_this_frame )
		Error(LOCATION, "Unable to allocate memory for OpenGL texture slots!");


	memset( Tex_used_this_frame, 0, MAX_BITMAPS * sizeof(int) );


	for (i = 0; i < MAX_BITMAPS; i++) {
		Textures[i].reset();
	}


	GL_mipmap_filter = os_config_read_uint(NULL, "TextureFilter", 1);

	if (GL_mipmap_filter > 1) {
		GL_mipmap_filter = 1;
	}


	if ( Is_Extension_Enabled(OGL_EXT_FRAMEBUFFER_OBJECT) ) {
		glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE_EXT, &GL_max_renderbuffer_size);


		if (GL_max_renderbuffer_size < 128) {
			mprintf(("WARNING: Max dimensions of FBO, %ix%i, is less the required minimum!!  Extension will be disabled!\n", GL_max_renderbuffer_size, GL_max_renderbuffer_size));
			GL_Extensions[OGL_EXT_FRAMEBUFFER_OBJECT].enabled = 0;
		}
	}


	if ( Is_Extension_Enabled(OGL_EXT_TEXTURE_FILTER_ANISOTROPIC) ) {

		opengl_get_max_anisotropy();


		char *plevel = os_config_read_string( NULL, NOX("OGL_AnisotropicFilter"), NOX("1.0") );
		GL_anisotropy = (GLfloat) strtod(plevel, (char**)NULL);

		CLAMP(GL_anisotropy, 1.0f, GL_max_anisotropy);
	}

	if ( Is_Extension_Enabled(OGL_EXT_TEXTURE_LOD_BIAS) ) {
		if (GL_anisotropy > 1.0f) {
			glTexEnvf(GL_TEXTURE_FILTER_CONTROL, GL_TEXTURE_LOD_BIAS, 0.0f);
		} else {
			glTexEnvf(GL_TEXTURE_FILTER_CONTROL, GL_TEXTURE_LOD_BIAS, -0.75f);
		}
	}


	memset( GL_xlat, 0, sizeof(GL_xlat) );

	for (i = 1; i < 15; i++) {
		GL_xlat[i] = (ubyte)(GL_xlat[i-1] + 17);
	}

	GL_xlat[15] = GL_xlat[1];

	glGetIntegerv(GL_MAX_TEXTURE_UNITS_ARB, &GL_supported_texture_units);
	Assert( GL_supported_texture_units >= 2 );

	GL_last_detail = Detail.hardware_textures;

	GL_textures_in = 0;
	GL_textures_in_frame = 0;
}

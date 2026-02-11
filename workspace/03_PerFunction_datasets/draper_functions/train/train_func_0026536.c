_evas_gl_common_shader_source_init(Evas_GL_Shared *shared)
{
  unsigned int i;

  for (i = 0; i < sizeof (_shaders_source) / sizeof (_shaders_source[0]); ++i)
    if (!_evas_gl_common_shader_program_source_init(&(shared->shader[_shaders_source[i].id]),
                                                    _shaders_source[i].vert,
                                                    _shaders_source[i].frag,
                                                    _shaders_source[i].name))
        return 0;

   return 1;
}

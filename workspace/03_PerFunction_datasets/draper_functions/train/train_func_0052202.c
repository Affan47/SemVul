tex_target_name(GLenum tgt)
{
   static const struct {
      GLenum target;
      const char *name;
   } tex_targets[] = {
      { GL_TEXTURE_1D, "GL_TEXTURE_1D" },
      { GL_TEXTURE_2D, "GL_TEXTURE_2D" },
      { GL_TEXTURE_3D, "GL_TEXTURE_3D" },
      { GL_TEXTURE_CUBE_MAP, "GL_TEXTURE_CUBE_MAP" },
      { GL_TEXTURE_RECTANGLE, "GL_TEXTURE_RECTANGLE" },
      { GL_TEXTURE_1D_ARRAY_EXT, "GL_TEXTURE_1D_ARRAY" },
      { GL_TEXTURE_2D_ARRAY_EXT, "GL_TEXTURE_2D_ARRAY" },
      { GL_TEXTURE_CUBE_MAP_ARRAY, "GL_TEXTURE_CUBE_MAP_ARRAY" },
      { GL_TEXTURE_BUFFER, "GL_TEXTURE_BUFFER" },
      { GL_TEXTURE_2D_MULTISAMPLE, "GL_TEXTURE_2D_MULTISAMPLE" },
      { GL_TEXTURE_2D_MULTISAMPLE_ARRAY, "GL_TEXTURE_2D_MULTISAMPLE_ARRAY" },
      { GL_TEXTURE_EXTERNAL_OES, "GL_TEXTURE_EXTERNAL_OES" }
   };
   GLuint i;
   STATIC_ASSERT(Elements(tex_targets) == NUM_TEXTURE_TARGETS);
   for (i = 0; i < Elements(tex_targets); i++) {
      if (tex_targets[i].target == tgt)
         return tex_targets[i].name;
   }
   return "UNKNOWN TEX TARGET";
}

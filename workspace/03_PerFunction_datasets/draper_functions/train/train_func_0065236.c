load_shader( GLData *gld, GLenum type, const char *shader_src )
{
   Evas_GL_API *gl = gld->glapi;
   GLuint shader;
   GLint compiled;


   shader = gl->glCreateShader(type);
   if (shader==0)
      return 0;


   gl->glShaderSource(shader, 1, &shader_src, NULL);
   gl->glCompileShader(shader);
   gl->glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

   if (!compiled)
     {
        GLint info_len = 0;
        gl->glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);
        if (info_len > 1)
          {
             char* info_log = malloc(sizeof(char) * info_len);

             gl->glGetShaderInfoLog(shader, info_len, NULL, info_log);
             printf("Error compiling shader:\n%s\n======\n%s\n======\n", info_log, shader_src );
             free(info_log);
          }
        gl->glDeleteShader(shader);
        return 0;
     }

   return shader;
}

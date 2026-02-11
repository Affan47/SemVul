_mesa_new_program(struct gl_context *ctx, GLenum target, GLuint id)
{
   struct gl_program *prog;
   switch (target) {
   case GL_VERTEX_PROGRAM_ARB:
      prog = _mesa_init_vertex_program(ctx, CALLOC_STRUCT(gl_vertex_program),
                                       target, id );
      break;
   case GL_FRAGMENT_PROGRAM_NV:
   case GL_FRAGMENT_PROGRAM_ARB:
      prog =_mesa_init_fragment_program(ctx,
                                         CALLOC_STRUCT(gl_fragment_program),
                                         target, id );
      break;
   case MESA_GEOMETRY_PROGRAM:
      prog = _mesa_init_geometry_program(ctx,
                                         CALLOC_STRUCT(gl_geometry_program),
                                         target, id);
      break;
   default:
      _mesa_problem(ctx, "bad target in _mesa_new_program");
      prog = NULL;
   }
   return prog;
}

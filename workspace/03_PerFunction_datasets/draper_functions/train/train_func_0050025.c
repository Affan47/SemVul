_mesa_GetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype,
                               GLint* range, GLint* precision)
{
   const struct gl_program_constants *limits;
   const struct gl_precision *p;
   GET_CURRENT_CONTEXT(ctx);

   switch (shadertype) {
   case GL_VERTEX_SHADER:
      limits = &ctx->Const.Program[MESA_SHADER_VERTEX];
      break;
   case GL_FRAGMENT_SHADER:
      limits = &ctx->Const.Program[MESA_SHADER_FRAGMENT];
      break;
   default:
      _mesa_error(ctx, GL_INVALID_ENUM,
                  "glGetShaderPrecisionFormat(shadertype)");
      return;
   }

   switch (precisiontype) {
   case GL_LOW_FLOAT:
      p = &limits->LowFloat;
      break;
   case GL_MEDIUM_FLOAT:
      p = &limits->MediumFloat;
      break;
   case GL_HIGH_FLOAT:
      p = &limits->HighFloat;
      break;
   case GL_LOW_INT:
      p = &limits->LowInt;
      break;
   case GL_MEDIUM_INT:
      p = &limits->MediumInt;
      break;
   case GL_HIGH_INT:
      p = &limits->HighInt;
      break;
   default:
      _mesa_error(ctx, GL_INVALID_ENUM,
                  "glGetShaderPrecisionFormat(precisiontype)");
      return;
   }

   range[0] = p->RangeMin;
   range[1] = p->RangeMax;
   precision[0] = p->Precision;
}

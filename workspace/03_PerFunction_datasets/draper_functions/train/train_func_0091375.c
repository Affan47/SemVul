compute_fog_blend_factors(struct gl_context *ctx, GLvector4f *out, const GLvector4f *in)
{
   GLfloat end  = ctx->Fog.End;
   GLfloat *v = in->start;
   GLuint stride = in->stride;
   GLuint n = in->count;
   GLfloat (*data)[4] = out->data;
   GLfloat d;
   GLuint i;

   out->count = in->count;

   switch (ctx->Fog.Mode) {
   case GL_LINEAR:
      if (ctx->Fog.Start == ctx->Fog.End)
         d = 1.0F;
      else
         d = 1.0F / (ctx->Fog.End - ctx->Fog.Start);
      for ( i = 0 ; i < n ; i++, STRIDE_F(v, stride)) {
         const GLfloat z = *v;
         GLfloat f = (end - z) * d;
	 data[i][0] = CLAMP(f, 0.0F, 1.0F);
      }
      break;
   case GL_EXP:
      d = ctx->Fog.Density;
      for ( i = 0 ; i < n ; i++, STRIDE_F(v,stride)) {
         const GLfloat z = *v;
         NEG_EXP( data[i][0], d * z );
      }
      break;
   case GL_EXP2:
      d = ctx->Fog.Density*ctx->Fog.Density;
      for ( i = 0 ; i < n ; i++, STRIDE_F(v, stride)) {
         const GLfloat z = *v;
         NEG_EXP( data[i][0], d * z * z );
      }
      break;
   default:
      _mesa_problem(ctx, "Bad fog mode in make_fog_coord");
      return;
   }
}

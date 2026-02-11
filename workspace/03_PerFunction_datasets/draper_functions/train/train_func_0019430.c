_mesa_init_point(struct gl_context *ctx)
{
   GLuint i;

   ctx->Point.SmoothFlag = GL_FALSE;
   ctx->Point.Size = 1.0;
   ctx->Point.Params[0] = 1.0;
   ctx->Point.Params[1] = 0.0;
   ctx->Point.Params[2] = 0.0;
   ctx->Point._Attenuated = GL_FALSE;
   ctx->Point.MinSize = 0.0;
   ctx->Point.MaxSize
      = MAX2(ctx->Const.MaxPointSize, ctx->Const.MaxPointSizeAA);
   ctx->Point.Threshold = 1.0;


   ctx->Point.PointSprite = (ctx->API == API_OPENGL_CORE ||
                             ctx->API == API_OPENGLES2);

   ctx->Point.SpriteRMode = GL_ZERO;
   ctx->Point.SpriteOrigin = GL_UPPER_LEFT;
   for (i = 0; i < Elements(ctx->Point.CoordReplace); i++) {
      ctx->Point.CoordReplace[i] = GL_FALSE;
   }
}

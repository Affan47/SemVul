_mesa_scale_and_bias_depth_uint(const struct gl_context *ctx, GLuint n,
                                GLuint depthValues[])
{
   const GLdouble max = (double) 0xffffffff;
   const GLdouble scale = ctx->Pixel.DepthScale;
   const GLdouble bias = ctx->Pixel.DepthBias * max;
   GLuint i;
   for (i = 0; i < n; i++) {
      GLdouble d = (GLdouble) depthValues[i] * scale + bias;
      d = CLAMP(d, 0.0, max);
      depthValues[i] = (GLuint) d;
   }
}

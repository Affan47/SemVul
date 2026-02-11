sample_cube_nearest_mipmap_linear(struct gl_context *ctx,
                                  const struct gl_sampler_object *samp,
                                  const struct gl_texture_object *tObj,
                                  GLuint n, const GLfloat texcoord[][4],
                                  const GLfloat lambda[], GLfloat rgba[][4])
{
   GLuint i;
   ASSERT(lambda != NULL);
   for (i = 0; i < n; i++) {
      const struct gl_texture_image **images;
      GLfloat newCoord[4];
      GLint level = linear_mipmap_level(tObj, lambda[i]);
      level = MAX2(level - 1, 0);
      images = choose_cube_face(tObj, texcoord[i], newCoord);
      if (level >= tObj->_MaxLevel) {
         sample_2d_nearest(ctx, samp, images[tObj->_MaxLevel],
                           newCoord, rgba[i]);
      }
      else {
         GLfloat t0[4], t1[4];
         const GLfloat f = FRAC(lambda[i]);
         sample_2d_nearest(ctx, samp, images[level  ], newCoord, t0);
         sample_2d_nearest(ctx, samp, images[level+1], newCoord, t1);
         lerp_rgba(rgba[i], f, t0, t1);
      }
   }
   if (is_depth_texture(tObj)) {
      for (i = 0; i < n; i++) {
         apply_depth_mode(tObj->DepthMode, rgba[i][0], rgba[i]);
      }
   }
}

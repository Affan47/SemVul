sample_lambda_rect(struct gl_context *ctx,
                   const struct gl_sampler_object *samp,
		   const struct gl_texture_object *tObj, GLuint n,
		   const GLfloat texcoords[][4], const GLfloat lambda[],
		   GLfloat rgba[][4])
{
   GLuint minStart, minEnd, magStart, magEnd;


   compute_min_mag_ranges(samp, n, lambda,
                          &minStart, &minEnd, &magStart, &magEnd);

   if (minStart < minEnd) {
      if (samp->MinFilter == GL_NEAREST) {
         sample_nearest_rect(ctx, samp, tObj, minEnd - minStart,
                             texcoords + minStart, NULL, rgba + minStart);
      }
      else {
         sample_linear_rect(ctx, samp, tObj, minEnd - minStart,
                            texcoords + minStart, NULL, rgba + minStart);
      }
   }
   if (magStart < magEnd) {
      if (samp->MagFilter == GL_NEAREST) {
         sample_nearest_rect(ctx, samp, tObj, magEnd - magStart,
                             texcoords + magStart, NULL, rgba + magStart);
      }
      else {
         sample_linear_rect(ctx, samp, tObj, magEnd - magStart,
                            texcoords + magStart, NULL, rgba + magStart);
      }
   }
}

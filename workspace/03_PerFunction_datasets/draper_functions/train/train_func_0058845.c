sample_2d_footprint(struct gl_context *ctx,
                 const struct gl_sampler_object *samp,
                 const struct gl_texture_object *tObj,
                 const GLfloat texcoord[4],
                 const GLfloat dudx, const GLfloat dvdx,
                 const GLfloat dudy, const GLfloat dvdy, const GLint lod,
                 GLfloat rgba[])
{
   GLint level = lod > 0 ? lod : 0;
   GLfloat scaling = 1.0F / (1 << level);
   const struct gl_texture_image *img = tObj->Image[0][level];

   GLfloat ux = dudx * scaling;
   GLfloat vx = dvdx * scaling;
   GLfloat uy = dudy * scaling;
   GLfloat vy = dvdy * scaling;

   GLfloat Px2 = ux * ux + vx * vx;
   GLfloat Py2 = uy * uy + vy * vy;

   GLint numSamples;
   GLfloat ds;
   GLfloat dt;

   GLfloat num[4] = {0.0F, 0.0F, 0.0F, 0.0F};
   GLfloat newCoord[2];
   GLint s;


   if (Px2 > Py2) {
      numSamples = (GLint) ceilf(sqrtf(Px2));
      ds = ux / ((GLfloat) img->Width2);
      dt = vx / ((GLfloat) img->Height2);
   }
   else {
      numSamples = (GLint) ceilf(sqrtf(Py2));
      ds = uy / ((GLfloat) img->Width2);
      dt = vy / ((GLfloat) img->Height2);
   }

   for (s = 0; s<numSamples; s++) {
      newCoord[0] = texcoord[0] + ds * ((GLfloat)(s+1) / (numSamples+1) -0.5f);
      newCoord[1] = texcoord[1] + dt * ((GLfloat)(s+1) / (numSamples+1) -0.5f);

      sample_2d_linear(ctx, samp, img, newCoord, rgba);
      num[0] += rgba[0];
      num[1] += rgba[1];
      num[2] += rgba[2];
      num[3] += rgba[3];
   }

   rgba[0] = num[0] / numSamples;
   rgba[1] = num[1] / numSamples;
   rgba[2] = num[2] / numSamples;
   rgba[3] = num[3] / numSamples;
}

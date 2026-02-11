fetch_signed_red_rgtc1(const GLubyte *map,
                       GLint rowStride, GLint i, GLint j, GLfloat *texel)
{
   GLbyte red;
   signed_fetch_texel_rgtc(rowStride, (const GLbyte *) map,
                           i, j, &red, 1);
   texel[RCOMP] = BYTE_TO_FLOAT_TEX(red);
   texel[GCOMP] = 0.0;
   texel[BCOMP] = 0.0;
   texel[ACOMP] = 1.0;
}

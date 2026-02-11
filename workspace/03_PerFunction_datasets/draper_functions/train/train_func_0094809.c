extractsrc_u( GLubyte srcpixels[4][4], const GLubyte *srcaddr,
			  GLint srcRowStride, GLint numxpixels, GLint numypixels, GLint comps)
{
   GLubyte i, j;
   const GLubyte *curaddr;
   for (j = 0; j < numypixels; j++) {
      curaddr = srcaddr + j * srcRowStride * comps;
      for (i = 0; i < numxpixels; i++) {
	 srcpixels[j][i] = *curaddr;
	 curaddr += comps;
      }
   }
}

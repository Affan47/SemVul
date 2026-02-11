_mesa_dump_depth_buffer(const char *filename)
{
   GET_CURRENT_CONTEXT(ctx);
   const GLuint w = ctx->DrawBuffer->Width;
   const GLuint h = ctx->DrawBuffer->Height;
   GLuint *buf;
   GLubyte *buf2;
   GLuint i;

   buf = malloc(w * h * 4);
   buf2 = malloc(w * h * 3);

   _mesa_PushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);
   _mesa_PixelStorei(GL_PACK_ALIGNMENT, 1);
   _mesa_PixelStorei(GL_PACK_INVERT_MESA, GL_TRUE);

   _mesa_ReadPixels(0, 0, w, h, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, buf);


   for (i = 0; i < w * h; i++) {
      buf2[i*3+0] = (buf[i] >> 24) & 0xff;
      buf2[i*3+1] = (buf[i] >> 16) & 0xff;
      buf2[i*3+2] = (buf[i] >>  8) & 0xff;
   }

   printf("Writing %d x %d depth buffer to %s\n", w, h, filename);
   write_ppm(filename, buf2, w, h, 3, 0, 1, 2, GL_TRUE);

   _mesa_PopClientAttrib();

   free(buf);
   free(buf2);
}

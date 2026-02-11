write_texture_image(struct gl_texture_object *texObj,
                    GLuint face, GLuint level)
{
   struct gl_texture_image *img = texObj->Image[face][level];
   if (img) {
      GET_CURRENT_CONTEXT(ctx);
      struct gl_pixelstore_attrib store;
      GLubyte *buffer;
      char s[100];

      buffer = malloc(img->Width * img->Height
                                        * img->Depth * 4);

      store = ctx->Pack;
      ctx->Pack = ctx->DefaultPacking;

      ctx->Driver.GetTexImage(ctx, GL_RGBA, GL_UNSIGNED_BYTE, buffer, img);


      _mesa_snprintf(s, sizeof(s), "/tmp/tex%u.l%u.f%u.ppm", texObj->Name, level, face);

      printf("  Writing image level %u to %s\n", level, s);
      write_ppm(s, buffer, img->Width, img->Height, 4, 0, 1, 2, GL_FALSE);

      ctx->Pack = store;

      free(buffer);
   }
}

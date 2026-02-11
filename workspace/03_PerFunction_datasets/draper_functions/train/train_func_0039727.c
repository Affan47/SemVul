_mesa_clear_texture_object(struct gl_context *ctx,
                           struct gl_texture_object *texObj)
{
   GLuint i, j;

   if (texObj->Target == 0)
      return;

   for (i = 0; i < MAX_FACES; i++) {
      for (j = 0; j < MAX_TEXTURE_LEVELS; j++) {
         struct gl_texture_image *texImage = texObj->Image[i][j];
         if (texImage)
            _mesa_clear_texture_image(ctx, texImage);
      }
   }
}

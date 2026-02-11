_mesa_store_compressed_teximage(struct gl_context *ctx, GLuint dims,
                                struct gl_texture_image *texImage,
                                GLsizei imageSize, const GLvoid *data)
{

   if (dims == 1) {
      _mesa_problem(ctx, "Unexpected glCompressedTexImage1D call");
      return;
   }


   ASSERT(texImage);
   ASSERT(texImage->Width > 0);
   ASSERT(texImage->Height > 0);
   ASSERT(texImage->Depth > 0);


   if (!ctx->Driver.AllocTextureImageBuffer(ctx, texImage)) {
      _mesa_error(ctx, GL_OUT_OF_MEMORY, "glCompressedTexImage%uD", dims);
      return;
   }

   _mesa_store_compressed_texsubimage(ctx, dims, texImage,
                                      0, 0, 0,
                                      texImage->Width, texImage->Height, texImage->Depth,
                                      texImage->TexFormat,
                                      imageSize, data);
}

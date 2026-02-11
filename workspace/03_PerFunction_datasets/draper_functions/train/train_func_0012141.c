texture_size(const struct gl_texture_object *texObj)
{
   const GLuint numFaces = _mesa_num_tex_faces(texObj->Target);
   GLuint face, level, size = 0;

   for (face = 0; face < numFaces; face++) {
      for (level = 0; level < MAX_TEXTURE_LEVELS; level++) {
         const struct gl_texture_image *img = texObj->Image[face][level];
         if (img) {
            GLuint sz = _mesa_format_image_size(img->TexFormat, img->Width,
                                                img->Height, img->Depth);
            size += sz;
         }
      }
   }

   return size;
}

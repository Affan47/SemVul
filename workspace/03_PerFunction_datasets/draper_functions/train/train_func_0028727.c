_mesa_get_fallback_texture(struct gl_context *ctx, gl_texture_index tex)
{
   if (!ctx->Shared->FallbackTex[tex]) {

      const GLsizei width = 1, height = 1, depth = 1;
      GLubyte texel[4];
      struct gl_texture_object *texObj;
      struct gl_texture_image *texImage;
      mesa_format texFormat;
      GLuint dims, face, numFaces = 1;
      GLenum target;

      texel[0] =
      texel[1] =
      texel[2] = 0x0;
      texel[3] = 0xff;

      switch (tex) {
      case TEXTURE_2D_ARRAY_INDEX:
         dims = 3;
         target = GL_TEXTURE_2D_ARRAY;
         break;
      case TEXTURE_1D_ARRAY_INDEX:
         dims = 2;
         target = GL_TEXTURE_1D_ARRAY;
         break;
      case TEXTURE_CUBE_INDEX:
         dims = 2;
         target = GL_TEXTURE_CUBE_MAP;
         numFaces = 6;
         break;
      case TEXTURE_3D_INDEX:
         dims = 3;
         target = GL_TEXTURE_3D;
         break;
      case TEXTURE_RECT_INDEX:
         dims = 2;
         target = GL_TEXTURE_RECTANGLE;
         break;
      case TEXTURE_2D_INDEX:
         dims = 2;
         target = GL_TEXTURE_2D;
         break;
      case TEXTURE_1D_INDEX:
         dims = 1;
         target = GL_TEXTURE_1D;
         break;
      case TEXTURE_BUFFER_INDEX:
         dims = 0;
         target = GL_TEXTURE_BUFFER;
         break;
      case TEXTURE_CUBE_ARRAY_INDEX:
         dims = 3;
         target = GL_TEXTURE_CUBE_MAP_ARRAY;
         break;
      case TEXTURE_EXTERNAL_INDEX:
         dims = 2;
         target = GL_TEXTURE_EXTERNAL_OES;
         break;
      case TEXTURE_2D_MULTISAMPLE_INDEX:
         dims = 2;
         target = GL_TEXTURE_2D_MULTISAMPLE;
         break;
      case TEXTURE_2D_MULTISAMPLE_ARRAY_INDEX:
         dims = 3;
         target = GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
         break;
      default:

         return NULL;
      }


      texObj = ctx->Driver.NewTextureObject(ctx, 0, target);
      if (!texObj)
         return NULL;

      assert(texObj->RefCount == 1);
      texObj->Sampler.MinFilter = GL_NEAREST;
      texObj->Sampler.MagFilter = GL_NEAREST;

      texFormat = ctx->Driver.ChooseTextureFormat(ctx, target,
                                                  GL_RGBA, GL_RGBA,
                                                  GL_UNSIGNED_BYTE);


      for (face = 0; face < numFaces; face++) {
         GLenum faceTarget;

         if (target == GL_TEXTURE_CUBE_MAP)
            faceTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X + face;
         else
            faceTarget = target;


         texImage = _mesa_get_tex_image(ctx, texObj, faceTarget, 0);

         _mesa_init_teximage_fields(ctx, texImage,
                                    width,
                                    (dims > 1) ? height : 1,
                                    (dims > 2) ? depth : 1,
                                    0,
                                    GL_RGBA, texFormat);

         ctx->Driver.TexImage(ctx, dims, texImage,
                              GL_RGBA, GL_UNSIGNED_BYTE, texel,
                              &ctx->DefaultPacking);
      }

      _mesa_test_texobj_completeness(ctx, texObj);
      assert(texObj->_BaseComplete);
      assert(texObj->_MipmapComplete);

      ctx->Shared->FallbackTex[tex] = texObj;
   }
   return ctx->Shared->FallbackTex[tex];
}

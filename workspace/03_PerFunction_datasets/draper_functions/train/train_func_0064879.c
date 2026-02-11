radeon_create_image(__DRIscreen *screen,
                    int width, int height, int format,
                    unsigned int use,
                    void *loaderPrivate)
{
   __DRIimage *image;
   radeonScreenPtr radeonScreen = screen->driverPrivate;

   image = calloc(1, sizeof *image);
   if (image == NULL)
      return NULL;

   image->dri_format = format;

   switch (format) {
   case __DRI_IMAGE_FORMAT_RGB565:
      image->format = MESA_FORMAT_B5G6R5_UNORM;
      image->internal_format = GL_RGB;
      image->data_type = GL_UNSIGNED_BYTE;
      break;
   case __DRI_IMAGE_FORMAT_XRGB8888:
      image->format = MESA_FORMAT_B8G8R8X8_UNORM;
      image->internal_format = GL_RGB;
      image->data_type = GL_UNSIGNED_BYTE;
      break;
   case __DRI_IMAGE_FORMAT_ARGB8888:
      image->format = MESA_FORMAT_B8G8R8A8_UNORM;
      image->internal_format = GL_RGBA;
      image->data_type = GL_UNSIGNED_BYTE;
      break;
   default:
      free(image);
      return NULL;
   }

   image->data = loaderPrivate;
   image->cpp = _mesa_get_format_bytes(image->format);
   image->width = width;
   image->height = height;
   image->pitch = ((image->cpp * image->width + 255) & ~255) / image->cpp;

   image->bo = radeon_bo_open(radeonScreen->bom,
                              0,
                              image->pitch * image->height * image->cpp,
                              0,
                              RADEON_GEM_DOMAIN_VRAM,
                              0);

   if (image->bo == NULL) {
      free(image);
      return NULL;
   }

   return image;
}

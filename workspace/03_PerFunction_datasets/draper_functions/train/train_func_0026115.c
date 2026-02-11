_eglQuerySurface(_EGLDriver *drv, _EGLDisplay *dpy, _EGLSurface *surface,
                 EGLint attribute, EGLint *value)
{
   switch (attribute) {
   case EGL_WIDTH:
      *value = surface->Width;
      break;
   case EGL_HEIGHT:
      *value = surface->Height;
      break;
   case EGL_CONFIG_ID:
      *value = surface->Config->ConfigID;
      break;
   case EGL_LARGEST_PBUFFER:
      *value = surface->LargestPbuffer;
      break;
   case EGL_TEXTURE_FORMAT:

      if (surface->Type == EGL_PBUFFER_BIT)
         *value = surface->TextureFormat;
      break;
   case EGL_TEXTURE_TARGET:
      if (surface->Type == EGL_PBUFFER_BIT)
         *value = surface->TextureTarget;
      break;
   case EGL_MIPMAP_TEXTURE:
      if (surface->Type == EGL_PBUFFER_BIT)
         *value = surface->MipmapTexture;
      break;
   case EGL_MIPMAP_LEVEL:
      if (surface->Type == EGL_PBUFFER_BIT)
         *value = surface->MipmapLevel;
      break;
   case EGL_SWAP_BEHAVIOR:
      *value = surface->SwapBehavior;
      break;
   case EGL_RENDER_BUFFER:
      *value = surface->RenderBuffer;
      break;
   case EGL_PIXEL_ASPECT_RATIO:
      *value = surface->AspectRatio;
      break;
   case EGL_HORIZONTAL_RESOLUTION:
      *value = surface->HorizontalResolution;
      break;
   case EGL_VERTICAL_RESOLUTION:
      *value = surface->VerticalResolution;
      break;
   case EGL_MULTISAMPLE_RESOLVE:
      *value = surface->MultisampleResolve;
      break;
   case EGL_VG_ALPHA_FORMAT:
      *value = surface->VGAlphaFormat;
      break;
   case EGL_VG_COLORSPACE:
      *value = surface->VGColorspace;
      break;
   case EGL_POST_SUB_BUFFER_SUPPORTED_NV:
      *value = surface->PostSubBufferSupportedNV;
      break;
   case EGL_BUFFER_AGE_EXT:
      if (!dpy->Extensions.EXT_buffer_age) {
         _eglError(EGL_BAD_ATTRIBUTE, "eglQuerySurface");
         return EGL_FALSE;
      }
      *value = drv->API.QueryBufferAge(drv, dpy, surface);
      break;
   default:
      _eglError(EGL_BAD_ATTRIBUTE, "eglQuerySurface");
      return EGL_FALSE;
   }

   return EGL_TRUE;
}

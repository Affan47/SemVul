_mesa_init_texture_s3tc( struct gl_context *ctx )
{

   ctx->Mesa_DXTn = GL_FALSE;
#if USE_EXTERNAL_DXTN_LIB
   if (!dxtlibhandle) {
      dxtlibhandle = _mesa_dlopen(DXTN_LIBNAME, 0);
      if (!dxtlibhandle) {
	 _mesa_warning(ctx, "couldn't open " DXTN_LIBNAME ", software DXTn "
	    "compression/decompression unavailable");
      }
      else {

         fetch_ext_rgb_dxt1 = (dxtFetchTexelFuncExt)
            _mesa_dlsym(dxtlibhandle, "fetch_2d_texel_rgb_dxt1");
         fetch_ext_rgba_dxt1 = (dxtFetchTexelFuncExt)
            _mesa_dlsym(dxtlibhandle, "fetch_2d_texel_rgba_dxt1");
         fetch_ext_rgba_dxt3 = (dxtFetchTexelFuncExt)
            _mesa_dlsym(dxtlibhandle, "fetch_2d_texel_rgba_dxt3");
         fetch_ext_rgba_dxt5 = (dxtFetchTexelFuncExt)
            _mesa_dlsym(dxtlibhandle, "fetch_2d_texel_rgba_dxt5");
         ext_tx_compress_dxtn = (dxtCompressTexFuncExt)
            _mesa_dlsym(dxtlibhandle, "tx_compress_dxtn");

         if (!fetch_ext_rgb_dxt1 ||
             !fetch_ext_rgba_dxt1 ||
             !fetch_ext_rgba_dxt3 ||
             !fetch_ext_rgba_dxt5 ||
             !ext_tx_compress_dxtn) {
	    _mesa_warning(ctx, "couldn't reference all symbols in "
	       DXTN_LIBNAME ", software DXTn compression/decompression "
	       "unavailable");
            fetch_ext_rgb_dxt1 = NULL;
            fetch_ext_rgba_dxt1 = NULL;
            fetch_ext_rgba_dxt3 = NULL;
            fetch_ext_rgba_dxt5 = NULL;
            ext_tx_compress_dxtn = NULL;
            _mesa_dlclose(dxtlibhandle);
            dxtlibhandle = NULL;
         }
      }
   }
   if (dxtlibhandle) {
      ctx->Mesa_DXTn = GL_TRUE;
   }
#else
   (void) ctx;
#endif
}

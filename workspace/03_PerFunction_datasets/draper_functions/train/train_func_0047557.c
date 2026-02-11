Probe( IDirectFBFont_ProbeContext *ctx )
{
     FT_Error err;
     FT_Face  face;

     D_DEBUG( "DirectFB/FontFT2: Probe font `%s'.\n", ctx->filename );

     if (!ctx->filename)
          return DFB_UNSUPPORTED;

     if (init_freetype() != DFB_OK) {
          return DFB_FAILURE;
     }

     pthread_mutex_lock ( &library_mutex );


     err = FT_New_Face( library, ctx->filename, 0, &face );
     if (!err)
          FT_Done_Face( face );
     pthread_mutex_unlock ( &library_mutex );

     release_freetype();

     return err ? DFB_UNSUPPORTED : DFB_OK;
}

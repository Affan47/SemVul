_mesa_GetnPixelMapusvARB( GLenum map, GLsizei bufSize, GLushort *values )
{
   GET_CURRENT_CONTEXT(ctx);
   GLint mapsize, i;
   const struct gl_pixelmap *pm;

   pm = get_pixelmap(ctx, map);
   if (!pm) {
      _mesa_error(ctx, GL_INVALID_ENUM, "glGetPixelMapusv(map)");
      return;
   }

   mapsize = pm->Size;

   if (!validate_pbo_access(ctx, &ctx->Pack, mapsize, GL_INTENSITY,
                            GL_UNSIGNED_SHORT, bufSize, values)) {
      return;
   }

   values = (GLushort *) _mesa_map_pbo_dest(ctx, &ctx->Pack, values);
   if (!values) {
      if (_mesa_is_bufferobj(ctx->Pack.BufferObj)) {
         _mesa_error(ctx, GL_INVALID_OPERATION,
                     "glGetPixelMapusv(PBO is mapped)");
      }
      return;
   }

   switch (map) {

   case GL_PIXEL_MAP_I_TO_I:
      for (i = 0; i < mapsize; i++) {
         values[i] = (GLushort) CLAMP(ctx->PixelMaps.ItoI.Map[i], 0.0, 65535.);
      }
      break;
   case GL_PIXEL_MAP_S_TO_S:
      for (i = 0; i < mapsize; i++) {
         values[i] = (GLushort) CLAMP(ctx->PixelMaps.StoS.Map[i], 0.0, 65535.);
      }
      break;
   default:
      for (i = 0; i < mapsize; i++) {
         CLAMPED_FLOAT_TO_USHORT(values[i], pm->Map[i] );
      }
   }

   _mesa_unmap_pbo_dest(ctx, &ctx->Pack);
}

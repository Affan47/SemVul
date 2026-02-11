FillRectAlpha( short x, short y, unsigned short w, unsigned short h,
                            const Color &col, unsigned char alpha  ) const {
  Uint8 *bits, bpp;
  SDL_PixelFormat *fmt = s_surface->format;


  bpp = fmt->BytesPerPixel;
  if ( bpp < 2 ) return FillRect( x, y, w, h, col );

  SurfaceLock lck( this );

  for ( int py = y; py < y + h; ++py ) {
    bits = ((Uint8 *)s_surface->pixels) + py * s_surface->pitch + x * bpp;

    for ( int px = x; px < x + w; ++px ) {
      unsigned char r, g, b;
      Uint32 pixel = 0;


      switch ( bpp ) {
        case 2:
          pixel = *((Uint16 *)(bits));
          break;
        case 3:
          if ( SDL_BYTEORDER == SDL_LIL_ENDIAN )
            pixel = bits[0] + (bits[1] << 8) + (bits[2] << 16);
          else
            pixel = (bits[0] << 16) + (bits[1] << 8) + bits[2];
          break;
        case 4:
          pixel = *((Uint32 *)(bits));
          break;
      }


      r = (((pixel&fmt->Rmask)>>fmt->Rshift)<<fmt->Rloss);
      g = (((pixel&fmt->Gmask)>>fmt->Gshift)<<fmt->Gloss);
      b = (((pixel&fmt->Bmask)>>fmt->Bshift)<<fmt->Bloss);


      r = (((col.r-r)*alpha)>>8) + r;
      g = (((col.g-g)*alpha)>>8) + g;
      b = (((col.b-b)*alpha)>>8) + b;
      DrawPixel( px, py, Color( r, g, b ) );

      bits += bpp;
    }
  }

  return 0;
}

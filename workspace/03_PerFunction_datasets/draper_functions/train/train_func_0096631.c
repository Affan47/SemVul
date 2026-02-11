hasTransparency( const Surface& surf )
{
   if ( surf.GetPixelFormat().BytesPerPixel() == 4 ) {
      const Uint32* p = (const Uint32*) surf.pixels();
      int aMask = surf.GetPixelFormat().Amask();
      int aShift = surf.GetPixelFormat().Ashift();
      for ( int y = 0; y < surf.h() ; ++y ) {
         for ( int x = 0; x < surf.w() ; ++x)
            if ( ((p[x] & aMask) >> aShift ) != Surface::opaque )
               return true;
         p += surf.pitch() / 4;
      }
   }
   return false;
}

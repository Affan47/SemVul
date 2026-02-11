toBGI() const
{
   void* p = malloc( imagesize(1,1,w(),h()) );
   char* c = (char*) p;
   Uint16* ww = (Uint16*) p;
   ww[0] = w()-1;
   ww[1] = h()-1;
   c += 4;
   for ( int y = 0; y < h(); ++y )
      for ( int x = 0; x < w(); ++x )
          *c++ = GetPixel(x,y);
   return p;
}

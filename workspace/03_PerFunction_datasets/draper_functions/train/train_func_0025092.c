createNewSurface()
{
   Surface s;
   if ( map.xsize > 0 && map.ysize > 0 ) {
      s =  Surface::createSurface( (map.xsize+1) * 6, 4 + map.ysize * 2 , 32, 0 );
   }
   return s;
}

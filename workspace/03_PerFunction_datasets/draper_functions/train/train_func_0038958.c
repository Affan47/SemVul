getResourcePlus( )
{
   Work* w = spawnWorkClasses ( true );
   Resources r;
   if ( w )
      r = w->getPlus();
   delete w;


   return r;
}

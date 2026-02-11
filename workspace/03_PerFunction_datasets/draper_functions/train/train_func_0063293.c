unlock()
{
   if ( !widget )
      return;

   if ( locked ) {
      widget->lockStandardActions(-1);
      locked = false;
   }
}

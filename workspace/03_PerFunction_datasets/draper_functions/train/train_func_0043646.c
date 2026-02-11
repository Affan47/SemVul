raiseLock()
{
   if ( theMapDisplay ) {
      ++theMapDisplay->lock;
      theMapDisplay->dirty = Map;
      theMapDisplay->Update();
   }
   lockMapdisplay();

}

setBusyState(MSBoolean state_)
{
  if (state_==MSTrue)
   {
     if (busyCount()==0) XDefineCursor(display(),_window,_server->watchCursor());
     _busyCount++;
   }
  else
   {
     if (busyCount()==1) XUndefineCursor(display(),_window);
     if (busyCount()>0) _busyCount--;
   }
}

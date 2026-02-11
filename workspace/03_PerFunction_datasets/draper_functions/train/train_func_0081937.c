button1Release(const XEvent *)
{
  if (armed()==MSTrue)
   {
     activate();
     disarm();

     XEvent event;
     while (XCheckWindowEvent(display(),window(),
                              ButtonPressMask|ButtonReleaseMask|Button1MotionMask,
                              &event));
   }
}

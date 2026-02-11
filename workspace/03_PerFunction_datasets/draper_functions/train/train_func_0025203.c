motion_compress( int x, int y, const XEvent *xEvent )
{
     if (motionX.axisabs != x) {
          motionX.type    = DIET_AXISMOTION;
          motionX.flags   = DIEF_AXISABS | DIEF_TIMESTAMP;
          motionX.axis    = DIAI_X;
          motionX.axisabs = x;

          motionX.timestamp.tv_sec  =  xEvent->xmotion.time / 1000;
          motionX.timestamp.tv_usec = (xEvent->xmotion.time % 1000) * 1000;
     }

     if (motionY.axisabs != y) {
          motionY.type    = DIET_AXISMOTION;
          motionY.flags   = DIEF_AXISABS | DIEF_TIMESTAMP;
          motionY.axis    = DIAI_Y;
          motionY.axisabs = y;

          motionY.timestamp.tv_sec  =  xEvent->xmotion.time / 1000;
          motionY.timestamp.tv_usec = (xEvent->xmotion.time % 1000) * 1000;
     }
}

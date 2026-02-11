unzoom(int xx, int yy) {
   pair<bigint, bigint> oldpos = at(xx, yy);
   mag-- ;
   int x2c = xx * 2 - getxmax() ;
   bigint o = x2c ;
   o.mulpow2(-mag-2) ;
   x -= o ;
   int y2c = yy * 2 - getymax() ;
   o = y2c ;
   o.mulpow2(-mag-2) ;
   y -= o ;
   reposition() ;

   pair<bigint, bigint> newpos = at(xx, yy);
   bigint xdrift = newpos.first;
   bigint ydrift = newpos.second;
   xdrift -= oldpos.first;
   ydrift -= oldpos.second;

   if (xdrift != 0) move(-xdrift.toint() << mag, 0);
   if (ydrift != 0) move(0, -ydrift.toint() << mag);
}

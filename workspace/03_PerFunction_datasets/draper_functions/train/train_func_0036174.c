move(int dx, int dy) {

   if (mag > 0) {
      dx /= (1 << mag) ;
      dy /= (1 << mag) ;
   }
   bigint addx = dx ;
   bigint addy = dy ;
   if (mag < 0) {
      addx <<= -mag ;
      addy <<= -mag ;
   }
   x += addx ;
   y += addy ;
   reposition() ;
}

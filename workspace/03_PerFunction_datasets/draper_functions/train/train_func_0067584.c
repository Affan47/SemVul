getnextfield(int&       x,
                          int&       y,
                          int       direc)
{
   switch (direc) {

      case 0:
         y-=2   ;
         break;

      case 1:
         if ((y & 1) == 1) x+=1;
         y-=1;
         break;

      case 2:
         if ((y & 1) == 1) x+=1;
         y+=1;
         break;

      case 3:
         y+=2;
         break;

      case 4:
         if ((y & 1) == 0) x-=1;
         y+=1;
         break;

      case 5:
         if ((y & 1) == 0) x-=1;
         y-=1;
         break;

   }
}

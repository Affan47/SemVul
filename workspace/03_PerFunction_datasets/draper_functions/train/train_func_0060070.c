gma_print(void)
{
   static const GUTF8String space(' ');
   GUTF8String res=GUTF8String('(')+POLY_TAG+space;
   for(int i=0;i<points;i++)
   {
      GUTF8String buffer;
      res+=buffer.format("%d %d ", xx[i], yy[i]);
   }
   res.setat(res.length()-1, ')');
   res+=space;
   return res;
}

update_group(int *pl, int *pm)
{
   int g;

   g=pm-I;
   V[*pl]=g;
   if (pl==pm)
      *pl=-1;
   else
      do
         V[*++pl]=g;
      while (pl<pm);
}

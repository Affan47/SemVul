adjust(int xa,int ya,int x,int y,int xb,int yb)
{
   S32 pseudoRandom;

   pseudoRandom = ((S32)iparmx)*((misc.rand()-16383));


   pseudoRandom = pseudoRandom * recur1;
   pseudoRandom = pseudoRandom >> SHIFT_VALUE;
   pseudoRandom = (((S32)get_pix(xa,ya)+(S32)get_pix(xb,yb)+1)>>1)+pseudoRandom;

   if (pseudoRandom >= MAX_COLOR)
      pseudoRandom = MAX_COLOR-1;

   if(pseudoRandom < 1)
      pseudoRandom = 1;

   plot(x,y,(U16)pseudoRandom);
	return((U16)pseudoRandom);
}
